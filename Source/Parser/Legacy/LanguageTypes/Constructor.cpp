/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Constructor.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/Constructor.h"

#include <boost/algorithm/string/join.hpp>

Constructor::Constructor(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , Invokable( cursor )
    , m_parent( parent )
{
        
}

bool Constructor::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Constructor::CompileTemplate(
    const ReflectionParser *context
) const
{
    TemplateData data { TemplateData::Type::Object };

    data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;

    auto enableNonDynamic = !m_metaData.GetFlag( native_property::DisableNonDynamicCtor );

    if (enableNonDynamic)
        data[ "templateParameters" ] = getTemplateParameters( false );

    data[ "dynamicTemplateParameters" ] = getTemplateParameters( true );

    data[ "enableNonDynamic" ] = utils::TemplateBool( enableNonDynamic );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Constructor::isAccessible(void) const
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

std::string Constructor::getTemplateParameters(bool isDynamic) const
{
    std::vector<std::string> params;

    // ClassType
    params.push_back( m_parent->m_qualifiedName );

    // IsDynamic
    params.emplace_back( isDynamic ? "true" : "false" );

    // IsWrapped
    params.emplace_back( 
        m_metaData.GetFlag( native_property::DynamicCtorWrap ) ? "true" : "false"
    );

    // Args...
    params.insert( params.end( ), m_signature.begin( ), m_signature.end( ) );

    return boost::join( params, ", " );
}