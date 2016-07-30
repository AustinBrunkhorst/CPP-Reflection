/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Field.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "Field.h"
#include "Method.h"

namespace ursine
{
    namespace meta
    {
        Field::Field(void)
            : m_type( Type::Invalid( ) )
            , m_classType( Type::Invalid( ) )
            , m_name( "INVALID" )
            , m_getter( nullptr ) 
            , m_setter( nullptr ) { }

        Field::Field(
            const std::string &name, 
            Type type, 
            Type classType, 
            FieldGetterBase *getter,
            FieldSetterBase *setter
        ) 
            : m_type( type )
            , m_classType( classType )
            , m_name( name )
            , m_getter( getter )
            , m_setter( setter ) { }

        const Field &Field::Invalid(void)
        {
            static Field field;

            return field;
        }

        bool Field::SetValue(Variant &instance, const Variant &value, const Method &setter)
        {
             // read only?
            if (!instance.IsConst( ))
            {
                setter.Invoke( instance, value );

                return true;
            }

            return false;
        }

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

        Variant Field::GetValue(const Variant &instance) const
        {
            return m_getter->GetValue( instance );
        }

        Variant Field::GetValueReference(const Variant &instance) const
        {
            return m_getter->GetValueReference( instance );
        }

        bool Field::SetValue(Variant &instance, const Variant &value) const
        {
            // read only?
            if (m_setter && !instance.IsConst( ))
            {
                m_setter->SetValue( instance, value );

                return true;
            }

            return false;
        }
    }
}
