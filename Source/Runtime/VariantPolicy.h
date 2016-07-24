/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** VariantPolicy.h
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        namespace variant_policy
        {
            /** @brief Wraps an Object pointer, rather than copying the value.
             *         This also ensures base class pointers can resolve their inherited type
             */
            struct WrapObject { };

            /** @brief Uses a reference to a value rather than copying it
             */
            struct NoCopy { };
        }
    }
}