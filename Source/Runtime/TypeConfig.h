/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeConfig.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaTraits.h"

#include <type_traits>

// Converts the type name into a meta::Type instance
#define typeof(expr)                                                  \
    ursine::meta::Type(                                               \
        ursine::meta::TypeInfo<                                       \
            ursine::meta::CleanedType<                                \
                typename ursine::meta_traits::RemoveArray<expr>::type \
            >                                                         \
        >::ID,                                                        \
        ursine::meta_traits::IsArray<expr>::value                     \
    )                                                                 \

// Converts the resulting type of the given expression to a meta::Type instance
#define decltypeof(expr) typeof( decltype( expr ) )

namespace ursine
{
    namespace meta
    {
        template<typename T>
        using CleanedType = 
            typename std::remove_cv< 
                typename std::remove_reference< T >::type 
            >::type;

        typedef unsigned TypeID;
    }
}