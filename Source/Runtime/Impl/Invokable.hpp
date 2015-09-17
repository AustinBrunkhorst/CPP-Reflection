#include "Type.h"
#include "TypeUnpacker.hpp"

#include <boost/functional/hash.hpp>

namespace std
{
    template<>
    struct hash<ursine::meta::InvokableSignature>
    {
        size_t operator()(
            const ursine::meta::InvokableSignature &signature
        ) const
        {
            size_t seed = 0;

            // combine the hash of all type IDs in the signature
            for (auto &type : signature)
                boost::hash_combine( seed, type.GetID( ) );

            return seed;
        }
    };
}

namespace ursine
{
    namespace meta
    {
        template<typename ...Types>
        InvokableSignature Invokable::CreateSignature(void)
        {
            static InvokableSignature signature;

            static auto initial = true;

            if (initial)
            {
                TypeUnpacker<Types...>::Apply( signature );

                initial = false;
            }

            return signature;
        }
    }
}