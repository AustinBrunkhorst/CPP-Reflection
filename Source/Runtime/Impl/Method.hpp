#include "TypeUnpacker.hpp"

namespace ursine
{
    namespace meta
    {
        template<class ClassType, typename ReturnType, typename ...ArgTypes>
        Method::Method(
            const std::string &name, 
            ReturnType(ClassType::*method)(ArgTypes...), 
            Invoker invoker
        )
            : Invokable( name )
            , m_isConst( false )
            , m_classType( typeof( ClassType ) )
            , m_invoker( invoker )
        {
            TypeUnpacker<ArgTypes...>::Apply( m_signature );
        }

        template<class ClassType, typename ReturnType, typename ...ArgTypes>
        Method::Method(
            const std::string &name, 
            ReturnType(ClassType::*method)(ArgTypes...) const, 
            Invoker invoker
        )
            : Invokable( name )
            , m_isConst( true )
            , m_classType( typeof( ClassType ) )
            , m_invoker( invoker )
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