/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FieldSetter.h
** --------------------------------------------------------------------------*/

#pragma once

#include "FieldSetterBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, typename FieldType, bool IsMethod>
        class FieldSetter : public FieldSetterBase
        {
        public:
            void SetValue(Variant &obj, const Variant &value) override;
        };
    }
}

#include "Impl/FieldSetter.hpp"