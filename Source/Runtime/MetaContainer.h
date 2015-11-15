/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** MetaContainer.h
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