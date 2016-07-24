/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** GlobalGetter.h
** --------------------------------------------------------------------------*/

#pragma once

#include "GlobalGetterBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename GlobalType, bool IsMethod>
        class GlobalGetter : public GlobalGetterBase
        {
        public:
            Variant GetValue(void) override;
        };
    }
}

#include "Impl/GlobalGetter.hpp"