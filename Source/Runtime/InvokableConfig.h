/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** InvokableConfig.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
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