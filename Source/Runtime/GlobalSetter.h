/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** GlobalSetter.h
** --------------------------------------------------------------------------*/

#pragma once

#include "GlobalSetterBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename GlobalType, bool IsMethod>
        class GlobalSetter : public GlobalSetterBase
        {
        public:
            void SetValue(const Argument &value) override;
        };
    }
}

#include "Impl/GlobalSetter.hpp"