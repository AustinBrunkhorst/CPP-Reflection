#include "TypeInfo.h"
#include "TypeUnpacker.hpp"

#include "Constructor.h"

namespace ursine
{
    namespace meta
    {
        template<typename T>
        Type Type::Get(T &&obj)
        {
            return { typeof( T ) };
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ... Args>
        Variant Type::Create(Args &&...args) const
        {
            static InvokableSignature signature;

            static bool initial = true;

            if (initial)
            {
                TypeUnpacker<Args...>::Apply( signature );

                initial = false;
            }

            auto &constructor = GetConstructor( signature );

            ArgumentList arguments { std::forward<Args>( args )... };

            return constructor.Invoke( arguments );
        }

        template <typename ... Args>
        Variant Type::CreateDynamic(Args&&... args) const
        {
            static InvokableSignature signature;

            static bool initial = true;

            if (initial)
            {
                TypeUnpacker<Args...>::Apply( signature );

                initial = false;
            }

            auto &constructor = GetDynamicConstructor( signature );

            ArgumentList arguments { std::forward<Args>( args )... };

            return constructor.Invoke( arguments );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        bool Type::DerivesFrom(void) const
        {
            return DerivesFrom( typeof( T ) );
        }
    }
}