/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/Method.h"

#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>

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
    TemplateData data { TemplateData::Type::Object };

    data[ "name" ] = m_name;
        
    data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;

    data[ "qualifiedSignature" ] = getQualifiedSignature( );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Method::isAccessible(void) const
{
    if (m_accessModifier != CX_CXXPublic)
        return false;

    // if the parent wants white listed method, then we must have 
    // the enable flag
    if (m_parent->GetMetaData( ).GetFlag( native_property::WhiteListMethods ))
        return m_metaData.GetFlag( native_property::Enable );

    // must not be explicitly disabled
    return !m_metaData.GetFlag( native_property::Disable );
}

std::string Method::getQualifiedSignature(void) const
{
    auto argsList = boost::join( m_signature, ", " );

    std::string constNess = m_isConst ? " const" : "";

    return (boost::format( "%1%(%2%::*)(%3%)%4%" ) % 
        m_returnType % 
        m_parent->m_qualifiedName % 
        argsList % constNess
    ).str( );
}