#include "Precompiled.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/Method.h"

#include <Utils.h>

#include <boost/format.hpp>

Method::Method(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , Invokable( cursor )
    , m_isConst( cursor.IsConst( ) )
    , m_parent( parent )
    , m_name( cursor.GetSpelling( ) )
{
    
}

bool Method::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Method::CompileTemplate(const ReflectionParser *context) const
{
    TemplateData data = { TemplateData::Type::Object };

    data[ "name" ] = m_name;
        
    data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;
    
    data[ "isVoidReturnType" ] = 
        utils::TemplateBool( m_returnType == kReturnTypeVoid );

    data[ "qualifiedSignature" ] = getQualifiedSignature( );

    data[ "invocationBody" ] = 
        context->LoadTemplatePartial( kPartialMethodInvocation );

    data[ "argument" ] = compileSignatureTemplate( );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Method::isAccessible(void) const
{
    return m_accessModifier == CX_CXXPublic && 
           !m_metaData.GetFlag( kMetaDisable );
}

std::string Method::getQualifiedSignature(void) const
{
    std::string argsList;

    ursine::utils::Join( m_signature, ", ", argsList );

    std::string constNess = m_isConst ? " const" : "";

    return (boost::format( "%1%(%2%::*)(%3%)%4%" ) % 
        m_returnType % 
        m_parent->m_qualifiedName % 
        argsList % constNess
    ).str( );
}