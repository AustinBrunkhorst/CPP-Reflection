/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** VariantBase.h
** --------------------------------------------------------------------------*/

#pragma once

#include <string>

#include "JsonConfig.h"

namespace ursine
{
    namespace meta
    {
        class Type;
        class ArrayWrapper;

        class VariantBase
        {
        public:
            virtual ~VariantBase(void) { }

            virtual Type GetType(void) const = 0;

            virtual void *GetPtr(void) const = 0;

            virtual int ToInt(void) const = 0;
            virtual bool ToBool(void) const = 0;
            virtual float ToFloat(void) const = 0;
            virtual double ToDouble(void) const = 0;
            virtual std::string ToString(void) const = 0;

            virtual bool IsArray(void) const;
            virtual ArrayWrapper GetArray(void) const;

            virtual VariantBase *Clone(void) const = 0;

            virtual void OnSerialize(Json::object &output) const { }
            virtual void OnDeserialize(const Json &input) { }
        };
    }
}