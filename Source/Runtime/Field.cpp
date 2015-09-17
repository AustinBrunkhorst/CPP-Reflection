#include "UrsinePrecompiled.h"

#include "Field.h"

namespace ursine
{
    namespace meta
    {
        Field::Field(void)
            : m_type( { Type::Invalid } ) 
            , m_classType( { Type::Invalid } )
            , m_name( "INVALID" )
            , m_getter( nullptr ) 
            , m_setter( nullptr ) { }

        Field::Field(
            const std::string &name, 
            Type type, 
            Type classType, 
            Getter getter, 
            Setter setter
        ) 
            : m_type( type )
            , m_classType( classType )
            , m_name( name )
            , m_getter( getter )
            , m_setter( setter ) { }

        bool Field::IsValid(void) const
        {
            return m_getter != nullptr;
        }

        bool Field::IsReadOnly(void) const
        {
            return m_setter == nullptr;
        }

        Type Field::GetType(void) const
        {
            return m_type;
        }

        Type Field::GetClassType(void) const
        {
            return m_classType;
        }

        const std::string &Field::GetName(void) const
        {
            return m_name;
        }

        Variant Field::GetValue(Variant &instance) const
        {
            return m_getter( instance );
        }

        bool Field::SetValue(Variant &instance, const Variant &value) const
        {
            // read only?
            if (m_setter && !instance.IsConst( ))
            {
                m_setter( instance, value );

                return true;
            }

            return false;
        }
    }
}
