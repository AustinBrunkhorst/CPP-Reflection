/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaTraits.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Array.h"

namespace ursine
{
    namespace meta_traits
    {
        template<typename T, typename = void>
        struct TypeOrEnumType
        {
            typedef T type;
        };

        template<typename T>
        struct TypeOrEnumType<T,
            typename std::enable_if<
            std::is_enum<T>::value
            >::type
        >
        {
            typedef typename std::underlying_type<T>::type type;
        };

        ///////////////////////////////////////////////////////////////////////////

        template<typename T>
        struct RemoveArray
        {
            typedef T type;
        };

        template<typename T>
        struct RemoveArray<Array<T>>
        {
            typedef T type;
        };

        ///////////////////////////////////////////////////////////////////////////

        template<typename T>
        struct IsArray
        {
            static const bool value = false;
        };

        template<typename T>
        struct IsArray<Array<T>>
        {
            static const bool value = true;
        };

        ///////////////////////////////////////////////////////////////////////////

        template<typename T>
        using ArrayByValue = Array<T>;

        template<typename T>
        using ArrayByReference = typename std::add_lvalue_reference<Array<T>>::type;
    }
}
