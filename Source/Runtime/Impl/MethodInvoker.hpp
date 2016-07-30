/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MethodInvoker.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        MethodInvoker<ClassType, ReturnType, ArgTypes...>::MethodInvoker(Signature method)
            : m_method( reinterpret_cast<ConstSignature>( method ) ) { }

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        MethodInvoker<ClassType, ReturnType, ArgTypes...>::MethodInvoker(ConstSignature method)
            : m_method( method ) { }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::Invoke(Variant &obj, const ArgumentList &arguments)
        {
            UAssert( arguments.size( ) == THIS_ARG_COUNT,
                "Invalid method arguments.\nExpected %i args but got %i.",
                THIS_ARG_COUNT,
                arguments.size( )
            );

            return invoke<void, ArgTypes...>( obj, arguments );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)( );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( ),
                arguments[ 4 ].GetValue<A5>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( ),
                arguments[ 4 ].GetValue<A5>( ),
                arguments[ 5 ].GetValue<A6>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
                arguments[ 0 ].GetValue<A1>( ),
                arguments[ 1 ].GetValue<A2>( ),
                arguments[ 2 ].GetValue<A3>( ),
                arguments[ 3 ].GetValue<A4>( ),
                arguments[ 4 ].GetValue<A5>( ),
                arguments[ 5 ].GetValue<A6>( ),
                arguments[ 6 ].GetValue<A7>( )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
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

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
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

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ReturnType, typename ... ArgTypes>
        template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
        Variant MethodInvoker<ClassType, ReturnType, ArgTypes...>::invoke(Variant &obj, const ArgumentList &arguments)
        {
            auto &instance = obj.GetValue<ClassType>( );

            return (instance.*m_method)(
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
