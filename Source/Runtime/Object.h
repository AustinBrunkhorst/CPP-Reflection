/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Object.h
** --------------------------------------------------------------------------*/

#pragma once

#include "JsonConfig.h"

// Constructs a variant that wraps an object
#define ObjectVariant(object) ursine::meta::Variant { object, ursine::meta::variant_policy::WrapObject( ) }

namespace ursine
{
    namespace meta
    {
        class Type;

        class Object
        {
        public:
            virtual ~Object(void) { }

            virtual Type GetType(void) const = 0;
            virtual Object *Clone(void) const = 0;

            virtual void OnSerialize(Json::object &output) const { }
            virtual void OnDeserialize(const Json &input) { }
        };
    }
}