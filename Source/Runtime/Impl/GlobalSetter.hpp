/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** GlobalSetter.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        ///////////////////////////////////////////////////////////////////////
        // Setter from Method
        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType>
        class GlobalSetter<GlobalType, true> : public GlobalSetterBase
        {
        public:
            typedef GlobalType(*Signature)(const GlobalType &);

            GlobalSetter(Signature function)
                : m_function( function ) { }

            void SetValue(const Argument &value) override
            {
                m_function( value.GetValue<GlobalType>( ) );
            }

        private:
            Signature m_function;
        };

        ///////////////////////////////////////////////////////////////////////
        // Setter from Direct Field
        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType>
        class GlobalSetter<GlobalType, false> : public GlobalSetterBase
        {
        public:
            GlobalSetter(GlobalType *field)
                : m_field( field ) { }

            void SetValue(const Argument &value) override
            {
                const_cast<GlobalType&>( *m_field ) = value.GetValue<GlobalType>( );
            }

        private:
            GlobalType *m_field;
        };
    }
}