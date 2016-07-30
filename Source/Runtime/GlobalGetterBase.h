/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** GlobalGetterBase.h
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        class Variant;

        class GlobalGetterBase
        {
        public:
            virtual ~GlobalGetterBase(void) { }

            virtual Variant GetValue(void) = 0;
        };
    }
}