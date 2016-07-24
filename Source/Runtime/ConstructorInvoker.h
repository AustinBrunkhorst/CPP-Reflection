/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ConstructorInvoker.h
** --------------------------------------------------------------------------*/

#pragma once

#include "ConstructorInvokerBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, bool IsDynamic, bool IsObjectWrapped, typename ...ArgTypes>
        class ConstructorInvoker : public ConstructorInvokerBase
        {
        public:
            static const size_t ArgCount = sizeof...( ArgTypes );

            static_assert( ArgCount <= MaxArgumentCount,
                "Constructor has too many arguments. It's time to generate more overloads." 
            );

            Variant Invoke(const ArgumentList &arguments) override;
        };
    }
}

#include "Impl/ConstructorInvoker.hpp"