/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FieldSetter.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        ///////////////////////////////////////////////////////////////////////
        // Setter from Method
        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ArgumentType>
        class FieldSetter<ClassType, ArgumentType, true> : public FieldSetterBase
        {
        public:
            typedef typename std::remove_reference<ArgumentType>::type NonReferenceArgType;
            typedef void (ClassType::*Signature)(ArgumentType);
            typedef void (ClassType::*SignatureConst)(ArgumentType) const;

            FieldSetter(Signature method)
                : m_method( method ) { }

            FieldSetter(SignatureConst method)
                : m_method( reinterpret_cast<Signature>( method ) ) { }

            void SetValue(Variant &obj, const Variant &value) override
            {
                UAssert( value.IsValid( ), "Setting invalid value." );

                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)( value.GetValue<NonReferenceArgType>( ) );
            }

        private:
            Signature m_method;
        };

        ///////////////////////////////////////////////////////////////////////
        // Setter from Direct Field
        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType>
        class FieldSetter<ClassType, FieldType, false> : public FieldSetterBase
        {
        public:
            typedef FieldType (ClassType::*Signature);
            typedef typename std::remove_const<FieldType>::type NonConstFieldType;

            FieldSetter(Signature field)
                : m_field( field ) { }

            void SetValue(Variant &obj, const Variant &value) override
            {
                UAssert( value.IsValid( ), "Setting invalid value." );

                auto &instance = obj.GetValue<ClassType>( );

                const_cast<NonConstFieldType&>( instance.*m_field ) = value.GetValue<FieldType>( );
            }

        private:
            Signature m_field;
        };
    }
}