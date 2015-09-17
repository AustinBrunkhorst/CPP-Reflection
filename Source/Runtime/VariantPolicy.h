/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** VariantPolicy.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
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