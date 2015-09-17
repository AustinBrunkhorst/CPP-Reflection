#include "Precompiled.h"

#include "LanguageTypes/Global.h"
#include "LanguageTypes/Class.h"

Global::Global(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , m_isConst( cursor.GetType( ).IsConst( ) )
    , m_hasExplicitGetter( m_metaData.GetFlag( kMetaExplicitGetter ) )
    , m_hasExplicitSetter( m_metaData.GetFlag( kMetaExplicitSetter ) )
    , m_parent( parent )
    , m_name( cursor.GetSpelling( ) )
    , m_qualifiedName( utils::GetQualifiedName( cursor, currentNamespace ) )
    , m_type( cursor.GetType( ).GetDisplayName( ) )
{
    auto displayName = m_metaData.GetNativeString( kMetaDisplayName );

    if (displayName.empty( ))
    {
        m_displayName = m_qualifiedName;
    }
    else
    {
        m_displayName = 
            utils::GetQualifiedName( displayName, currentNamespace );
    }
}

bool Global::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Global::CompileTemplate(const ReflectionParser *context) const
{
    TemplateData data = { TemplateData::Type::Object };

    data[ "name" ] = m_name;
    data[ "displayName" ] = m_displayName;
    data[ "qualifiedName" ] = m_qualifiedName;
    data[ "type" ] = m_type;

    data[ "hasParent" ] = utils::TemplateBool( !!m_parent );

    if (m_parent)
        data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;

    // getter

    data[ "isGetterAccessible" ] = 
        utils::TemplateBool( isGetterAccessible( ) );

    data[ "hasExplicitGetter" ] = 
        utils::TemplateBool( m_hasExplicitGetter );

    data[ "explicitGetter" ] = 
        m_metaData.GetProperty( kMetaExplicitGetter );

    data[ "getterBody" ] = 
        context->LoadTemplatePartial( kPartialGlobalGetter );

    // setter

    data[ "isSetterAccessible" ] = 
        utils::TemplateBool( isSetterAccessible( ) );

    data[ "hasExplicitSetter" ] = 
        utils::TemplateBool( m_hasExplicitSetter );

    data[ "explicitSetter" ] = 
        m_metaData.GetProperty( kMetaExplicitSetter );

    data[ "setterBody" ] = 
        context->LoadTemplatePartial( kPartialGlobalSetter );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Global::isAccessible(void) const
{
    return isGetterAccessible( ) || isSetterAccessible( );
}

bool Global::isGetterAccessible(void) const
{
    if (m_enabled)
    {
        if (m_parent)
            return m_hasExplicitGetter || m_accessModifier == CX_CXXPublic;

        return true;
    }

    return false;
}

bool Global::isSetterAccessible(void) const
{
    if (m_isConst)
        return false;

    if (m_enabled)
    {
        if (m_parent)
            return m_hasExplicitSetter || m_accessModifier == CX_CXXPublic;

        return true;
    }

    return false;
}