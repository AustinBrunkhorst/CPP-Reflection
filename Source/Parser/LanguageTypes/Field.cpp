#include "Precompiled.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/Field.h"

Field::Field(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , m_isConst( cursor.GetType( ).IsConst( ) )
    , m_parent( parent )
    , m_name( cursor.GetSpelling( ) )
    , m_type( cursor.GetType( ).GetDisplayName( ) )
{
    auto displayName = m_metaData.GetNativeString( kMetaDisplayName );

    if (displayName.empty( ))
        m_displayName = m_name;
    else
        m_displayName = displayName;

    m_explicitGetter = m_metaData.GetNativeString( kMetaExplicitGetter );
    m_hasExplicitGetter = !m_explicitGetter.empty( );

    m_explicitSetter = m_metaData.GetNativeString( kMetaExplicitSetter );
    m_hasExplicitSetter = !m_explicitSetter.empty( );
}

bool Field::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Field::CompileTemplate(const ReflectionParser *context) const
{
    TemplateData data = { TemplateData::Type::Object };

    data[ "name" ] = m_name;
    data[ "displayName" ] = m_displayName;
    data[ "type" ] = m_type;

    data[ "hasParent" ] = utils::TemplateBool( !!m_parent );

    data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;

    // getter

    data[ "isGetterAccessible" ] = utils::TemplateBool( isGetterAccessible( ) );
    data[ "hasExplicitGetter" ] = utils::TemplateBool( m_hasExplicitGetter );
    data[ "explicitGetter" ] = m_explicitGetter;
    data[ "getterBody" ] = context->LoadTemplatePartial( kPartialFieldGetter );

    // setter

    data[ "isSetterAccessible" ] = utils::TemplateBool( isSetterAccessible( ) );
    data[ "hasExplicitSetter" ] = utils::TemplateBool( m_hasExplicitSetter );
    data[ "explicitSetter" ] = m_explicitSetter;
    data[ "setterBody" ] = context->LoadTemplatePartial( kPartialFieldSetter );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Field::isAccessible(void) const
{
    return (m_hasExplicitGetter || m_hasExplicitSetter) ||
            (
                m_accessModifier == CX_CXXPublic && 
                !m_metaData.GetFlag( kMetaDisable )
            );
}

bool Field::isGetterAccessible(void) const
{
    return m_hasExplicitGetter || m_accessModifier == CX_CXXPublic;
}

bool Field::isSetterAccessible(void) const
{
    return m_hasExplicitSetter || 
           (!m_isConst && m_accessModifier == CX_CXXPublic);
}