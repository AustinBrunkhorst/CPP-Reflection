#include "Precompiled.h"

#include "ReflectionParser.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/Global.h"
#include "LanguageTypes/Function.h"
#include "LanguageTypes/Enum.h"

#include <boost/algorithm/string.hpp>

#define RECURSE_NAMESPACES(kind, cursor, method, ns) \
    if (kind == CXCursor_Namespace)                  \
    {                                                \
        auto displayName = cursor.GetDisplayName( ); \
        if (!displayName.empty( ))                   \
        {                                            \
            ns.emplace_back( displayName );          \
            method( cursor, ns );                    \
            ns.pop_back( );                          \
        }                                            \
    }                                                \

ReflectionParser::ReflectionParser(const ReflectionOptions &options)
    : m_options( options )
    , m_index( nullptr )
    , m_translationUnit( nullptr )
{
   
}

ReflectionParser::~ReflectionParser(void)
{
    for (auto *klass : m_classes)
        delete klass;

    for (auto *global : m_globals)
        delete global;

    for (auto *globalFunction : m_globalFunctions)
        delete globalFunction;

    for (auto *enewm : m_enums)
        delete enewm;

    if (m_translationUnit)
        clang_disposeTranslationUnit( m_translationUnit );

    if (m_index)
        clang_disposeIndex( m_index );
}

void ReflectionParser::Parse(void)
{
    m_index = clang_createIndex( true, false );

    std::vector<const char *> arguments;

    for (auto &argument : m_options.arguments)
    { 
        // unescape flags
        boost::algorithm::replace_all( argument, "\\-", "-" );

        arguments.emplace_back( argument.c_str( ) );
    }

    m_translationUnit = clang_createTranslationUnitFromSourceFile(
        m_index,
        m_options.inputSourceFile.c_str( ),
        static_cast<int>( arguments.size( ) ),
        arguments.data( ),
        0,
        nullptr
    );

    auto cursor = clang_getTranslationUnitCursor( m_translationUnit );

    Namespace tempNamespace;

    buildClasses( cursor, tempNamespace );

    tempNamespace.clear( );

    buildGlobals( cursor, tempNamespace );

    tempNamespace.clear( );

    buildGlobalFunctions( cursor, tempNamespace );

    tempNamespace.clear( );

    buildEnums( cursor, tempNamespace );
}

MustacheTemplate ReflectionParser::LoadTemplate(const std::string &name) const
{
    auto path = fs::path( m_options.templateDirectory );

    path.append( name );

    try
    {
        std::string text;

        utils::LoadText( path.string( ), text );

        return text;
    }
    catch(std::exception &e)
    {
        std::stringstream error;

        error << "Unable to load template ";
        error << name << "." << std::endl;
        error << "-- " << e.what( );

        utils::FatalError( error.str( ) );
    }

    // this will never happen
    return { "" };
}

TemplateData::PartialType ReflectionParser::LoadTemplatePartial(
    const std::string &name
) const
{
    auto path = 
        fs::path( m_options.templateDirectory ).append( name ).string( );

    try
    {
        auto partialLoader = [=]()
        {
            auto cache = m_templatePartialCache.find( path );

            if (cache == m_templatePartialCache.end( ))
            {
                std::string text;

                utils::LoadText( path, text );

                m_templatePartialCache[ path ] = text;

                return text;
            }
                
            return cache->second;
        };

        return partialLoader;
    }
    catch(std::exception &e)
    {
        std::stringstream error;

        error << "Unable to load template partial ";
        error << name << "." << std::endl;
        error << "-- " << e.what( );

        utils::FatalError( error.str( ) );
    }

    // this will never happen
    return nullptr;
}

void ReflectionParser::GenerateHeader(std::string &output) const
{
    TemplateData headerData { TemplateData::Type::Object };

    // general options

    headerData[ "targetName" ] = m_options.targetName;
    headerData[ "inputSourceFile" ] = m_options.inputSourceFile;
    headerData[ "ouputHeaderFile" ] = m_options.outputHeaderFile;
    headerData[ "outpuSourceFile" ] = m_options.outputSourceFile;

    headerData[ "usingPrecompiledHeader" ] = 
        utils::TemplateBool( !m_options.precompiledHeader.empty( ) );

    headerData[ "precompiledHeader" ] = m_options.precompiledHeader;

    auto headerTemplate = LoadTemplate( kTemplateHeader );

    if (!headerTemplate.isValid( ))
    {
        std::stringstream error;

        error << "Unable to compile header template." << std::endl;
        error << headerTemplate.errorMessage( );

        throw std::exception( error.str( ).c_str( ) );
    }

    output = headerTemplate.render( headerData );
}

void ReflectionParser::GenerateSource(std::string &output) const
{
    TemplateData sourceData { TemplateData::Type::Object };

    // general options

    sourceData[ "targetName" ] = m_options.targetName;
    sourceData[ "inputSourceFile" ] = m_options.inputSourceFile;
    sourceData[ "ouputHeaderFile" ] = m_options.outputHeaderFile;
    sourceData[ "outpuSourceFile" ] = m_options.outputSourceFile;

    sourceData[ "usingPrecompiledHeader" ] = 
        utils::TemplateBool( !m_options.precompiledHeader.empty( ) );

    sourceData[ "precompiledHeader" ] = m_options.precompiledHeader;

    // language type data

    sourceData[ "class" ] = compileClassTemplates( );
    sourceData[ "global" ] = compileGlobalTemplates( );
    sourceData[ "globalFunction" ] = compileGlobalFunctionTemplates( );
    sourceData[ "enum" ] = compileEnumTemplates( );

    auto sourceTemplate = LoadTemplate( kTemplateSource );

    if (!sourceTemplate.isValid( ))
    {
        std::stringstream error;

        error << "Unable to compile header template." << std::endl;
        error << sourceTemplate.errorMessage( );

        throw std::exception( error.str( ).c_str( ) );
    }

    output = sourceTemplate.render( sourceData );
}

void ReflectionParser::buildClasses(
    const Cursor &cursor, 
    Namespace &currentNamespace
)
{
    for (auto &child : cursor.GetChildren( ))
    {
        auto kind = child.GetKind( );

        // actual definition and a class or struct
        if (child.IsDefinition( ) && 
            (kind == CXCursor_ClassDecl || kind == CXCursor_StructDecl)
        )
        {
            m_classes.emplace_back( 
                new Class( child, currentNamespace )
            );
        }
        
        RECURSE_NAMESPACES( kind, child, buildClasses, currentNamespace );
    }
}

void ReflectionParser::buildGlobals(
    const Cursor &cursor, 
    Namespace &currentNamespace
)
{
    for (auto &child : cursor.GetChildren( ))
    {
        // skip static globals (hidden)
        if (child.GetStorageClass( ) == CX_SC_Static)
            continue;

        auto kind = child.GetKind( );

        // variable declaration, which is global
        if (kind == CXCursor_VarDecl) 
        {
            m_globals.emplace_back( 
                new Global( child, currentNamespace ) 
            );
        }

        RECURSE_NAMESPACES( kind, child, buildGlobals, currentNamespace );
    }
}

void ReflectionParser::buildGlobalFunctions(
    const Cursor &cursor, 
    Namespace &currentNamespace
)
{
    for (auto &child : cursor.GetChildren( ))
    {
        // skip static globals (hidden)
        if (child.GetStorageClass( ) == CX_SC_Static)
            continue;

        auto kind = child.GetKind( );

        // function declaration, which is global
        if (kind == CXCursor_FunctionDecl) 
        {
            m_globalFunctions.emplace_back( 
                new Function( child, currentNamespace ) 
            );
        }

        RECURSE_NAMESPACES( 
            kind, 
            child, 
            buildGlobalFunctions, 
            currentNamespace 
        );
    }
}

void ReflectionParser::buildEnums(
    const Cursor &cursor, 
    Namespace &currentNamespace
)
{
    for (auto &child : cursor.GetChildren( ))
    {
        auto kind = child.GetKind( );

        // actual definition and an enum
        if (child.IsDefinition( ) && kind == CXCursor_EnumDecl)
        {
            // anonymous enum if the underlying type display name contains this
            if (child.GetType( ).GetDisplayName( ).find( "anonymous enum at" ) 
                != std::string::npos)
            {
                // anonymous enums are just loaded as 
                // globals with each of their values
                Enum::LoadAnonymous( m_globals, child, currentNamespace );
            }
            else
            {
                m_enums.emplace_back( 
                    new Enum( child, currentNamespace ) 
                );
            }
        }

        RECURSE_NAMESPACES( kind, child, buildEnums, currentNamespace );
    }
}

TemplateData ReflectionParser::compileClassTemplates(void) const
{
    TemplateData data = { TemplateData::Type::List };

    for (auto *klass : m_classes)
    {
        if (klass->ShouldCompile( ))
            data << klass->CompileTemplate( this );
    }

    return data;
}

TemplateData ReflectionParser::compileGlobalTemplates(void) const
{
    TemplateData data = { TemplateData::Type::List };

    for (auto *global : m_globals)
    {
        if (global->ShouldCompile( ))
            data << global->CompileTemplate( this );
    }
       
    return data;
}

TemplateData ReflectionParser::compileGlobalFunctionTemplates(void) const
{
    TemplateData data = { TemplateData::Type::List };

    for (auto *globalFunction : m_globalFunctions)
    {
        if (globalFunction->ShouldCompile( ))
            data << globalFunction->CompileTemplate( this );
    }

    return data;
}

TemplateData ReflectionParser::compileEnumTemplates(void) const
{
    TemplateData data = { TemplateData::Type::List };

    for (auto *enewm : m_enums)
    {
        if (enewm->ShouldCompile( ))
            data << enewm->CompileTemplate( this );
    }

    return data;
}