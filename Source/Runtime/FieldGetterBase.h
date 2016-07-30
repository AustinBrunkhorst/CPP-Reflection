/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FieldGetterBase.h
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        class Variant;

        class FieldGetterBase
        {
        public:
            virtual ~FieldGetterBase(void) { }

            virtual Variant GetValue(const Variant &obj) = 0;
            virtual Variant GetValueReference(const Variant &obj) = 0;
        };
    }
}