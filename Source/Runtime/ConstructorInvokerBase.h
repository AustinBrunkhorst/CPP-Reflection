/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ConstructorInvokerBase.h
** --------------------------------------------------------------------------*/

#pragma once

#include "InvokableConfig.h"
#include "ArgumentConfig.h"

namespace ursine
{
    namespace meta
    {
        class Variant;
        class Argument;

        class ConstructorInvokerBase
        {
        public:
            virtual ~ConstructorInvokerBase(void) { }

            virtual Variant Invoke(const ArgumentList &arguments) = 0;
        };
    }
}