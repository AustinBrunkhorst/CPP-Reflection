/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** GlobalGetter.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        ///////////////////////////////////////////////////////////////////////
        // Getter from Method
        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType>
        class GlobalGetter<GlobalType, true> : public GlobalGetterBase
        {
        public:
            typedef GlobalType (*Signature)(void);

            GlobalGetter(Signature function)
                : m_function( function ) { }

            Variant GetValue(void) override
            {
                return m_function( );
            }

        private:
            Signature m_function;
        };

        ///////////////////////////////////////////////////////////////////////
        // Getter from Direct Global
        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType>
        class GlobalGetter<GlobalType, false> : public GlobalGetterBase
        {
        public:
            GlobalGetter(GlobalType *global)
                : m_global( global ) { }

            Variant GetValue(void) override
            {
                return *m_global;
            }

        private:
            GlobalType *m_global;
        };
    }
}