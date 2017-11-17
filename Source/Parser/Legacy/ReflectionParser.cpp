/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionParser.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "ReflectionParser.h"
#include "Version.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/External.h"
#include "LanguageTypes/Global.h"
#include "LanguageTypes/Function.h"
#include "LanguageTypes/Enum.h"

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <fstream>

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

#define TRY_ADD_LANGUAGE_TYPE(handle, container)                \
    if (handle->ShouldCompile( ))                               \
    {                                                           \
        auto file = handle->GetSourceFile( );                   \
        m_moduleFiles[ file ].container.emplace_back( handle ); \
    }                                                           \

#define COMPILE_TYPE_TEMPLATES(data, listName, container)   \
    {                                                       \
        TemplateData typeData { TemplateData::Type::List }; \
        for (auto &handle : container)                      \
            typeData << handle->CompileTemplate( this );    \
        data[ listName ] = typeData;                        \
    }                                                       \

namespace
{
    const boost::regex kSpecialCharsRegex( "[^a-zA-Z0-9]+" );
}

ReflectionParser::ReflectionParser(const ReflectionOptions &options)
    : m_options( options )
    , m_index( nullptr )
    , m_translationUnit( nullptr )
    , m_moduleFileHeaderTemplate( "" )
    , m_moduleFileSourceTemplate( "" )
{
    // replace special characters in target name with underscores
    m_options.targetName = boost::regex_replace(
        m_options.targetName, 
        kSpecialCharsRegex, 
        "_" 
    );
}

ReflectionParser::~ReflectionParser(void)
{
    if (m_translationUnit)
        clang_disposeTranslationUnit( m_translationUnit );

    if (m_index)
        clang_disposeIndex( m_index );
}

void ReflectionParser::Parse(void)
{
    m_index = clang_createIndex( true, m_options.displayDiagnostics );

    std::vector<const char *> arguments;

#if defined(SYSTEM_INCLUDE_DIRECTORY)

    arguments.emplace_back( "-I" SYSTEM_INCLUDE_DIRECTORY );

#endif

    for (auto &argument : m_options.arguments)
        arguments.emplace_back( argument.c_str( ) );

    if (m_options.displayDiagnostics)
    {
        for (auto *argument : arguments)
            std::cout << argument << std::endl;
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

void ReflectionParser::GenerateFiles(void)
{
    fs::path sourceRootDirectory( m_options.sourceRoot );
    fs::path outputFileDirectory( m_options.outputModuleFileDirectory );

    m_moduleFileHeaderTemplate = LoadTemplate( kTemplateModuleFileHeader );

    if (!m_moduleFileHeaderTemplate.isValid( ))
    {
        std::stringstream error;

        error << "Unable to compile module file header template." << std::endl;
        error << m_moduleFileHeaderTemplate.errorMessage( );

        throw std::runtime_error( error.str( ) );
    }

    m_moduleFileSourceTemplate = LoadTemplate( kTemplateModuleFileSource );

    if (!m_moduleFileSourceTemplate.isValid( ))
    {
        std::stringstream error;

        error << "Unable to compile module file source template." << std::endl;
        error << m_moduleFileSourceTemplate.errorMessage( );

        throw std::runtime_error( error.str( ) );
    }

    TemplateData moduleFilesData { TemplateData::Type::List };

    fs::path metaCacheFileName = m_options.outputModuleFileDirectory;

    metaCacheFileName /= ".meta-cache";

    auto metaCacheFileExists = exists( metaCacheFileName );

    std::string moduleFileCache;

    for (auto &file : m_moduleFiles)
    {
        fs::path filePath( file.first );

        // path relative to the source root
        auto relativeDir = utils::MakeRelativePath( sourceRootDirectory, filePath )
            .replace_extension( "" ).string( );

        if (relativeDir.find_first_of( ".." ) != std::string::npos)
            continue;

        auto outputFile = outputFileDirectory / relativeDir;
        auto outputFileHeader = change_extension( outputFile, "Generated.h" );
        auto outputFileSource = change_extension( outputFile, "Generated.cpp" );

        // module file name
        file.second.name = boost::regex_replace(
            relativeDir,
            kSpecialCharsRegex,
            "_"
        );

        moduleFileCache += file.second.name + "\n";

        TemplateData moduleFileData { TemplateData::Type::Object };

        moduleFileData[ "name" ] = file.second.name;
        moduleFileData[ "header" ] = outputFileHeader.string( );

        moduleFilesData << moduleFileData;

        // if the generated file header/source doesn't exist, we need to regenerate
        if (m_options.forceRebuild || 
            !metaCacheFileExists || 
            !exists( outputFileHeader ) ||
            !exists( outputFileSource )
        )
        {
            generateModuleFile( outputFileHeader, outputFileSource, file.first, file.second );

            continue;
        }

        auto lastSourceWrite = last_write_time( filePath );
        auto lastGeneratedHeaderWrite = last_write_time( outputFileHeader );
        auto lastGeneratedSourceWrite = last_write_time( outputFileSource );

        // if the generated file is older than the source file, we need to regenerate
        if (lastSourceWrite > lastGeneratedHeaderWrite || lastSourceWrite > lastGeneratedSourceWrite)
            generateModuleFile( outputFileHeader, outputFileSource, file.first, file.second );
    }

    if (!m_options.forceRebuild && metaCacheFileExists)
    {
        std::ifstream cacheFile( metaCacheFileName.string( ) );

        std::istreambuf_iterator<char> cacheFileBegin( cacheFile );
        std::istreambuf_iterator<char> cacheFileEnd( nullptr );
        
        // the cache is the same, so we don't need to write the source files
        if (utils::RangeEqual( 
                moduleFileCache.begin( ), moduleFileCache.end( ), 
                cacheFileBegin, cacheFileEnd 
            ))
        {
            return;
        }
    }

    // update the cache
    utils::WriteText(
        metaCacheFileName.string( ),
        moduleFileCache
    );

    // module source file
    {
        auto sourceTemplate = LoadTemplate( kTemplateModuleSource );

        if (!sourceTemplate.isValid( ))
        {
            std::stringstream error;

            error << "Unable to compile module source template." << std::endl;
            error << sourceTemplate.errorMessage( );

            throw std::runtime_error( error.str( ).c_str( ) );
        }

        TemplateData sourceData { TemplateData::Type::Object };

        addGlobalTemplateData( sourceData );

        sourceData[ "moduleFile" ] = moduleFilesData;

        COMPILE_TYPE_TEMPLATES( sourceData, "external", m_externals );

        fs::path sourcePath( m_options.outputModuleSource );

        fs::create_directory( sourcePath.parent_path( ) );

        utils::WriteText( 
            sourcePath.string( ),
            sourceTemplate.render( sourceData )
        );
    }
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
    catch (std::exception &e)
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
            auto klass = std::make_shared<Class>( child, currentNamespace );

            TRY_ADD_LANGUAGE_TYPE( klass, classes );
        }
        else if (kind == CXCursor_TypedefDecl)
        {
            auto displayName = child.GetDisplayName( );

            // external declaration; they're always compiled, but only registered
            if (boost::starts_with( displayName, kMetaExternalTypeDefName ))
            {
                m_externals.emplace_back(
                    std::make_shared<External>( child.GetTypedefType( ).GetDeclaration( ) )
                );
            }
        }
        
        RECURSE_NAMESPACES( kind, child, buildClasses, currentNamespace );
    }
}

void ReflectionParser::buildGlobals(
    const Cursor &cursor, 
    Namespace &currentNamespace
)
{
    auto children = cursor.GetChildren( );

    for (auto &child : children)
    {
        // skip static globals (hidden)
        if (child.GetStorageClass( ) == CX_SC_Static)
            continue;

        auto kind = child.GetKind( );

        // variable declaration, which is global
        if (kind == CXCursor_VarDecl) 
        {
            auto global = std::make_shared<Global>( child, currentNamespace );

            TRY_ADD_LANGUAGE_TYPE( global, globals );
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
            auto function = std::make_shared<Function>( child, currentNamespace );

            TRY_ADD_LANGUAGE_TYPE( function, globalFunctions );
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
                for (auto &enumChild : child.GetChildren( ))
                {
                    if (enumChild.GetKind( ) == CXCursor_EnumConstantDecl)
                    {
                        auto global = std::make_shared<Global>( enumChild, currentNamespace, nullptr );

                        TRY_ADD_LANGUAGE_TYPE( global, globals );
                    }
                }
            }
            else
            {
                auto enewm = std::make_shared<Enum>( child, currentNamespace );

                TRY_ADD_LANGUAGE_TYPE( enewm, enums );
            }
        }

        RECURSE_NAMESPACES( kind, child, buildEnums, currentNamespace );
    }
}

void ReflectionParser::addGlobalTemplateData(TemplateData &data)
{
    data[ "version" ] = kMetaGeneratorVersion;
    data[ "targetName" ] = m_options.targetName;
    data[ "inputSourceFile" ] = m_options.inputSourceFile;
    data[ "moduleHeaderFile" ] = m_options.moduleHeaderFile;
    data[ "outputModuleSourceFile" ] = m_options.outputModuleSource;

    data[ "usingPrecompiledHeader" ] =
        utils::TemplateBool( !m_options.precompiledHeader.empty( ) );

    data[ "precompiledHeader" ] = m_options.precompiledHeader;
}

void ReflectionParser::generateModuleFile(
    const fs::path &fileHeader,
    const fs::path &fileSource,
    const std::string &sourceHeader,
    const ModuleFile &file
)
{
    // header file
    {
        TemplateData headerData { TemplateData::Type::Object };

        addGlobalTemplateData( headerData );

        headerData[ "moduleFileName" ] = file.name;

        fs::create_directory( fileHeader.parent_path( ) );

        utils::WriteText( 
            fileHeader.string( ), 
            m_moduleFileHeaderTemplate.render( headerData ) 
        );
    }

    // source file
    {
        TemplateData sourceData { TemplateData::Type::Object };

        addGlobalTemplateData( sourceData );

        sourceData[ "moduleFileName" ] = file.name;
        sourceData[ "moduleFileSourceHeader" ] = sourceHeader;
        sourceData[ "moduleFileHeader" ] = fileHeader.string( );

        COMPILE_TYPE_TEMPLATES( sourceData, "class", file.classes );
        COMPILE_TYPE_TEMPLATES( sourceData, "global", file.globals );
        COMPILE_TYPE_TEMPLATES( sourceData, "globalFunction", file.globalFunctions );
        COMPILE_TYPE_TEMPLATES( sourceData, "enum", file.enums );

        fs::create_directory( fileSource.parent_path( ) );

        utils::WriteText( 
            fileSource.string( ),
            m_moduleFileSourceTemplate.render( sourceData ) 
        );
    }
}