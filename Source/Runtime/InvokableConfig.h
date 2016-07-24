/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
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

        // maximum number of arguments supported
        const size_t MaxArgumentCount = 10;
    }
}