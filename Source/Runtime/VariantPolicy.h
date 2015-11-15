/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
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
            /** @brief Wraps an Object pointer, rather than copying the value
            */
            struct WrapObject { };
        }
    }
}