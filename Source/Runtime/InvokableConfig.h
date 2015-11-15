/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** InvokableConfig.h
** --------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <unordered_map>

namespace ursine
{
    namespace meta
    {
        class Type;

        typedef std::vector<Type> InvokableSignature;

        template<typename T>
        using InvokableOverloadMap = 
            std::unordered_multimap<InvokableSignature, T>;
    }
}