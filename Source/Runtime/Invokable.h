/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Invokable.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "InvokableConfig.h"
#include "ArgumentConfig.h"

#include <vector>

namespace ursine
{
    namespace meta
    {
        class Type;

        class Invokable
        {
        public:
            Invokable(const std::string &name);

            template<typename ...Types>
            static InvokableSignature CreateSignature(void);

            const InvokableSignature &GetSignature(void) const;

            const std::string &GetName(void) const;

        protected:
            std::string m_name;

            InvokableSignature m_signature;
        };
    }
}

#include "Impl/Invokable.hpp"