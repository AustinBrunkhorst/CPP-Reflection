/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** MetaContainer.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaManager.h"

namespace ursine
{
    namespace meta
    {
        class MetaContainer
        {
        public:
            MetaManager &GetMeta(void);

        private:
            MetaContainer &operator=(const MetaContainer &rhs) = delete;

            friend class ReflectionDatabase;
            friend struct TypeData;

            MetaManager m_meta;
        };
    }
}