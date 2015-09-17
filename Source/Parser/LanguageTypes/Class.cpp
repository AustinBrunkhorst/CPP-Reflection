#include "Precompiled.h"

#include "LanguageTypes/Class.h"

#include "ReservedTypes.h"

namespace
{
    const std::vector<std::string> nativeTypes
    {
        kTypeObject,
        kTypeMetaProperty
    };

    bool isNativeType(const std::string &qualifiedName)
    {
        return std::find( 
            nativeTypes.begin( ), 
            nativeTypes.end( ), 
            qualifiedName
        ) != nativeTypes.end( );
    }
}

BaseClass::BaseClass(const Cursor &cursor)
    : name( cursor.GetType( ).GetCanonicalType( ).GetDisplayName( ) )
{

}

Class::Class(const Cursor &cursor, const Namespace &currentNamespace)
    : LanguageType( cursor, currentNamespace )
    , m_name( cursor.GetDisplayName( ) )
    , m_qualifiedName( cursor.GetType( ).GetDisplayName( ) )
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

    for (auto &child : cursor.GetChildren( ))
    {
        switch (child.GetKind( ))
        {
        case CXCursor_CXXBaseSpecifier:
        {
            auto baseClass = new BaseClass( child );

            m_baseClasses.emplace_back( baseClass );

            // automatically enable the type if not explicitly disabled
            if (isNativeType( baseClass->name ))
                m_enabled = !m_metaData.GetFlag( kMetaDisable );
        }
            break;
        // constructor
        case CXCursor_Constructor:
            m_constructors.emplace_back( 
                new Constructor( child, currentNamespace, this ) 
            );
            break;
        // field
        case CXCursor_FieldDecl:
            m_fields.emplace_back( 
                new Field( child, currentNamespace, this )
            );
            break;
        // static field
        case CXCursor_VarDecl:
            m_staticFields.emplace_back( 
                new Global( child, Namespace( ), this ) 
            );
            break;
        // method / static method
        case CXCursor_CXXMethod:
            if (child.IsStatic( )) 
            { 
                m_staticMethods.emplace_back( 
                    new Function( child, Namespace( ), this ) 
                );
            }
            else 
            { 
                m_methods.emplace_back( 
                    new Method( child, currentNamespace, this ) 
                );
            }
            break;
        default:
            break;
        }
    }
}

Class::~Class(void)
{
    for (auto *baseClass : m_baseClasses)
        delete baseClass;

    for (auto *constructor : m_constructors)
        delete constructor;

    for (auto *field : m_fields)
        delete field;

    for (auto *staticField : m_staticFields)
        delete staticField;

    for (auto *method : m_methods)
        delete method;

    for (auto *staticMethod : m_staticMethods)
        delete staticMethod;
}

bool Class::ShouldCompile(void) const
{
    return isAccessible( ) && !isNativeType( m_qualifiedName );
}

TemplateData Class::CompileTemplate(const ReflectionParser *context) const
{
    TemplateData data { TemplateData::Type::Object };

    data[ "displayName" ] = m_displayName;
    data[ "qualifiedName" ] = m_qualifiedName;
    data[ "ptrTypeEnabled" ] = utils::TemplateBool( m_ptrTypeEnabled );

    data[ "constPtrTypeEnabled" ] = 
        utils::TemplateBool( m_constPtrTypeEnabled );

    m_metaData.CompileTemplateData( data, context );

    // base classes
    {
        TemplateData baseClasses { TemplateData::Type::List };

        int i = 0;

        for (auto *baseClass : m_baseClasses)
        {
            // ignore native types
            if (isNativeType( baseClass->name ))
                continue;

            TemplateData item { TemplateData::Type::Object };

            item[ "name" ] = baseClass->name;

            item[ "isLast" ] = 
                utils::TemplateBool( i == m_baseClasses.size( ) - 1 );

            baseClasses << item;

            ++i;
        }

        data[ "baseClass" ] = baseClasses;
    }

    // constructors
    {
        TemplateData constructors { TemplateData::Type::List };

        for (auto *ctor : m_constructors)
        {
            if (ctor->ShouldCompile( ))
                constructors << ctor->CompileTemplate( context );
        }
            

        data[ "constructor" ] = constructors;
        data[ "dynamicConstructor" ] = constructors;
    }

    // fields
    {
        TemplateData fields { TemplateData::Type::List };

        for (auto *field : m_fields)
        {
            if (field->ShouldCompile( ))
                fields << field->CompileTemplate( context );
        }

        data[ "field" ] = fields;
    }

    // static fields
    {
        TemplateData staticFields { TemplateData::Type::List };

        for (auto *staticField : m_staticFields)
        {
            if (staticField->ShouldCompile( ))
                staticFields << staticField->CompileTemplate( context );
        }
            
        data[ "staticField" ] = staticFields;
    }

    // static fields
    {
        TemplateData methods { TemplateData::Type::List };

        for (auto *method : m_methods)
        {
            if (method->ShouldCompile( ))
                methods << method->CompileTemplate( context );
        }
           
        data[ "method" ] = methods;
    }

    // static fields
    {
        TemplateData staticMethods { TemplateData::Type::List };

        for (auto *staticMethod : m_staticMethods)
        {
            if (staticMethod->ShouldCompile( ))
                staticMethods << staticMethod->CompileTemplate( context );
        }

        data[ "staticMethod" ] = staticMethods;
    }

    return data;
}

bool Class::isAccessible(void) const
{
    return m_enabled;
}