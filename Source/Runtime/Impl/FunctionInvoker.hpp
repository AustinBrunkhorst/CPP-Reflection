/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FunctionInvoker.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename ReturnType, typename ... ArgTypes>
        FunctionInvoker<ReturnType, ArgTypes...>::FunctionInvoker(Signature function)
            : m_function( function ) { }

        template<typename ReturnType, typename ... ArgTypes>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::Invoke(const ArgumentList &arguments)
        {
            UAssert( arguments.size( ) == THIS_ARG_COUNT,
                "Invalid function arguments.\nExpected %i args but got %i.",
                THIS_ARG_COUNT,
                arguments.size( )
            );

            return invoke<void, ArgTypes...>( arguments );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function( );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( ),
                arguments[ 4 ].GetValue<A5>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( ),
                arguments[ 4 ].GetValue<A5>( ),
                arguments[ 5 ].GetValue<A6>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( ),
                arguments[ 4 ].GetValue<A5>( ),
                arguments[ 5 ].GetValue<A6>( ),
                arguments[ 6 ].GetValue<A7>( )
            );
        }

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
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

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
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

        template<typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
        Variant FunctionInvoker<ReturnType, ArgTypes...>::invoke(const ArgumentList &arguments)
        {
            return m_function(
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
    }
}
