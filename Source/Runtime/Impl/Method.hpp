/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "TypeUnpacker.hpp"

namespace ursine
{
    namespace meta
    {
        template<class ClassType, typename ReturnType, typename ...ArgTypes>
        Method::Method(
            const std::string &name, 
            ReturnType(ClassType::*method)(ArgTypes...)
        )
            : Invokable( name )
            , m_isConst( false )
            , m_classType( typeof( ClassType ) )
            , m_invoker( new MethodInvoker<ClassType, ReturnType, ArgTypes...>( method ) )
        {
            TypeUnpacker<ArgTypes...>::Apply( m_signature );
        }

        template<class ClassType, typename ReturnType, typename ...ArgTypes>
        Method::Method(
            const std::string &name, 
            ReturnType(ClassType::*method)(ArgTypes...) const
        )
            : Invokable( name )
            , m_isConst( true )
            , m_classType( typeof( ClassType ) )
            , m_invoker( new MethodInvoker<ClassType, ReturnType, ArgTypes...>( method ) )
        {
            TypeUnpacker<ArgTypes...>::Apply( m_signature );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ...Args>
        Variant Method::Invoke(Variant &instance, Args &&...args) const
        {
            ArgumentList arguments { std::forward<Args>( args )... };

            return Invoke( instance, arguments );
        }
    }
}