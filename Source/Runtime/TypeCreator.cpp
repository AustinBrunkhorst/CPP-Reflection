/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeCreator.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "TypeCreator.h"

namespace ursine
{
    namespace meta
    {
        Variant TypeCreator::CreateVariadic(const Type &type, const ArgumentList &arguments)
        {
            InvokableSignature signature;

            for (auto &argument : arguments)
                signature.emplace_back( argument.GetType( ) );

            auto &constructor = type.GetConstructor( signature );

            return constructor.Invoke( arguments );
        }

        Variant TypeCreator::CreateDynamicVariadic(const Type &type, const ArgumentList &arguments)
        {
            InvokableSignature signature;

            for (auto &argument : arguments)
                signature.emplace_back( argument.GetType( ) );

            auto &constructor = type.GetDynamicConstructor( signature );

            return constructor.Invoke( arguments );
        }
    }
}