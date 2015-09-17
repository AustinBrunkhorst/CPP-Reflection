#include "UrsinePrecompiled.h"

#include "MetaContainer.h"
#include "MetaManager.h"

namespace ursine
{
    namespace meta
    {
        MetaManager &MetaContainer::GetMeta(void)
        {
            return m_meta;
        }
    }
}