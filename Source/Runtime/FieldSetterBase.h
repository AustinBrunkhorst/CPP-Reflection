/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FieldSetterBase.h
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        class Variant;

        class FieldSetterBase
        {
        public:
            virtual ~FieldSetterBase(void) { }

            virtual void SetValue(Variant &obj, const Variant &value) = 0;
        };
    }
}