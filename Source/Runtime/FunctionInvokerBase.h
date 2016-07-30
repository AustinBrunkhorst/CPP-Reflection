/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FunctionInvokerBase.h
** --------------------------------------------------------------------------*/

#pragma once

#include "InvokableConfig.h"
#include "ArgumentConfig.h"

namespace ursine
{
    namespace meta
    {
        class Variant;

        class FunctionInvokerBase
        {
        public:
            virtual ~FunctionInvokerBase(void) { }

            virtual Variant Invoke(const ArgumentList &arguments) = 0;
        };
    }
}