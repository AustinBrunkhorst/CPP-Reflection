/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeInfo.h
** --------------------------------------------------------------------------*/

#pragma once

#include "TypeConfig.h"

#include "../Common/Compiler.h"

#include <type_traits>

#if defined(COMPILER_CLANG) || defined(COMPILER_GNU)

#define IsTriviallyDefaultConstructible(x) std::has_trivial_default_constructor<x>::value

#else

#define IsTriviallyDefaultConstructible(x) std::is_trivially_default_constructible<x>::value

#endif

namespace ursine
{
    namespace meta
    {
        struct TypeData;

        template<typename T>
        struct TypeInfo
        {
            static bool Defined;

            static void Register(TypeID id, TypeData &data, bool beingDefined);

        private:
            template<typename U = T>
            static void addDefaultConstructor(
                TypeData &data, 
                typename std::enable_if<
                    !IsTriviallyDefaultConstructible(U)
                >::type* = nullptr
            );

            template<typename U = T>
            static void addDefaultConstructor(
                TypeData &data, 
                typename std::enable_if<
                    IsTriviallyDefaultConstructible(U)
                >::type* = nullptr
            );

            template<typename U = T>
            static void applyTrivialAttributes(TypeData &data, 
                typename std::enable_if< 
                    !std::is_trivial<U>::value 
                >::type* = nullptr
            );

            template<typename U = T>
            static void applyTrivialAttributes(TypeData &data, 
                typename std::enable_if< 
                    std::is_trivial<U>::value 
                >::type* = nullptr
            );
        };
    }
}

#include "Impl/TypeInfo.hpp"
