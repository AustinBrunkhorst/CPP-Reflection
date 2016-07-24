/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ObjectWrapper.h
** --------------------------------------------------------------------------*/

#pragma once

#include "VariantBase.h"

#include "JsonConfig.h"

namespace ursine
{
    namespace meta
    {
        class Object;

        class ObjectWrapper : public VariantBase
        {
        public:
            ObjectWrapper(Object *instance);

            Type GetType(void) const override;
            void *GetPtr(void) const override;

            int ToInt(void) const override;
            bool ToBool(void) const override;
            float ToFloat(void) const override;
            double ToDouble(void) const override;
            std::string ToString(void) const override;

            VariantBase *Clone(void) const override;

            void OnSerialize(Json::object &output) const override;
            void OnDeserialize(const Json &input) override;
        private:
            Object *m_object;
        };
    }
}