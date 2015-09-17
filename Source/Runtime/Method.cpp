#include "UrsinePrecompiled.h"

#include "Method.h"

namespace ursine
{
    namespace meta
    {
        Method::Method(void)
            : Invokable( "INVALID" )
            , m_isConst( true )
            , m_classType( { Type::Invalid } )
            , m_invoker( nullptr ) { }

        const Method &Method::Invalid(void)
        {
            static Method invalid;

            return invalid;
        }

        Type Method::GetClassType(void) const
        {
            return m_classType;
        }

        bool Method::IsValid(void) const
        {
            return m_invoker != nullptr;
        }

        bool Method::IsConst(void) const
        {
            return m_isConst;
        }

        Variant Method::Invoke(
            Variant &instance,
            ArgumentList &arguments
        ) const
        {
        #ifdef CONFIG_DEBUG

            UAssert( IsValid( ), 
                "Invalid method invoked" );

            UAssert( instance.IsConst( ) && !m_isConst, 
                "Non-const method invoked on const object" )

            UAssert( instance.GetType( ) == m_classType, 
                "Incompatible method invoked with instance" );

        #endif

            return m_invoker( instance, arguments );
        }
    }
}
