#include "Precompiled.h"

#include "LanguageTypes/Function.h"
#include "LanguageTypes/Class.h"

#include <Utils.h>

#include <boost/format.hpp>

Function::Function(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , Invokable( cursor )
    , m_parent( parent )
    , m_name( cursor.GetSpelling( ) )
    , m_qualifiedName( utils::GetQualifiedName( cursor, currentNamespace ) )
{
        
}

bool Function::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Function::CompileTemplate(const ReflectionParser *context) const
{
    TemplateData data { TemplateData::Type::Object };

    data[ "name" ] = m_name;
    data[ "qualifiedName" ] = m_qualifiedName;

    if (m_parent)
        data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;
    
    data[ "isVoidReturnType" ] = 
        utils::TemplateBool( m_returnType == kReturnTypeVoid );

    data[ "qualifiedSignature" ] = getQualifiedSignature( );
    
    data[ "invocationBody" ] = 
        context->LoadTemplatePartial( kPartialFunctionInvocation );

    data[ "argument" ] = compileSignatureTemplate( );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Function::isAccessible(void) const
{
    if (m_parent && m_accessModifier != CX_CXXPublic)
        return false;

    return m_enabled;
}

std::string Function::getQualifiedSignature(void) const
{
    std::string argsList;

    ursine::utils::Join( m_signature, ", ", argsList );

    return (boost::format( "%1%(*)(%2%)" ) % m_returnType % argsList).str( );
}