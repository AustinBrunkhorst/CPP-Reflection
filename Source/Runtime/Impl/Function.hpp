/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Function.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename ReturnType, typename ...ArgTypes>
        Function::Function(
            const std::string &name, 
            ReturnType (*function)(ArgTypes...),
            Type parentType
        )
            : Invokable( name )
            , m_parentType( parentType )
            , m_invoker( new FunctionInvoker<ReturnType, ArgTypes...>( function ) )
        {
            TypeUnpacker<ArgTypes...>::Apply( m_signature );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ...Args>
        Variant Function::Invoke(Args &&...args) const
        {
            ArgumentList arguments { std::forward<Args>( args )... };

            return InvokeVariadic( arguments );
        }
    }
}
