/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeCreator.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "../Constructor.h"

namespace ursine
{
    namespace meta
    {
        template<typename ...Args>
        Variant TypeCreator::Create(const Type &type, Args &&...args)
        {
            static InvokableSignature signature;

            static bool initial = true;

            if (initial)
            {
                TypeUnpacker<Args...>::Apply( signature );

                initial = false;
            }

            auto &constructor = type.GetConstructor( signature );

            return constructor.Invoke( std::forward<Args>( args )... );
        }

        template<typename ...Args>
        Variant TypeCreator::CreateDynamic(const Type &type, Args &&...args)
        {
            static InvokableSignature signature;

            static bool initial = true;

            if (initial)
            {
                TypeUnpacker<Args...>::Apply( signature );

                initial = false;
            }

            auto &constructor = type.GetDynamicConstructor( signature );

            return constructor.Invoke( std::forward<Args>( args )... );
        }
    }
}