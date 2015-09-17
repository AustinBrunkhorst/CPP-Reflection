/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** TypeInfo.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "TypeConfig.h"

namespace ursine
{
    namespace meta
    {
        struct TypeData;

        template<typename T>
        struct TypeInfo
        {
            static TypeID ID;
            static bool Defined;

            static void Register(TypeID id, TypeData &data, bool beingDefined);

        private:
            template<typename U = T>
            static void addDefaultConstructor(
                TypeData &data, 
                typename std::enable_if< 
                    !std::is_trivially_default_constructible<U>::value 
                >::type* = nullptr
            );

            template<typename U = T>
            static void addDefaultConstructor(
                TypeData &data, 
                typename std::enable_if< 
                    std::is_trivially_default_constructible<U>::value 
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