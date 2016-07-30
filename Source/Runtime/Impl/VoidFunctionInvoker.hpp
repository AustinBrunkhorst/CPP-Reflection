/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** VoidFunctionInvoker.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename ...ArgTypes>
        class FunctionInvoker<void, ArgTypes...> : public FunctionInvokerBase
        {
        public:
            typedef void (*Signature)(ArgTypes...);

            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Function has too many arguments. It's time to generate more overloads." 
            );

            FunctionInvoker(Signature function)
                : m_function( function ) { }

            Variant Invoke(const ArgumentList &arguments) override
            {
                UAssert( arguments.size( ) == THIS_ARG_COUNT,
                    "Invalid function arguments.\nExpected %i args but got %i.",
                    THIS_ARG_COUNT,
                    arguments.size( )
                );

                invoke<void, ArgTypes...>( arguments );

                return { };
            }

        private:
            template<typename _>
            void invoke(const ArgumentList &arguments)
            {
                m_function( );
            }

            template<typename _, typename A1>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( )
                );
            }

            template<typename _, typename A1, typename A2>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            void invoke(const ArgumentList &arguments)
            {
                m_function(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( ),
                    arguments[ 9 ].GetValue<A10>( )
                );
            }

            Signature m_function;
        };
    }
}