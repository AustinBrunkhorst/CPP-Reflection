/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** InvokableConfig.h
** --------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <unordered_map>

// number of arguments within the usage of a dynamic method/function invoker
#define THIS_ARG_COUNT sizeof...( ArgTypes )

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