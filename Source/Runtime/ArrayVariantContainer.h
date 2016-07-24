/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ArrayVariantContainer.h
** --------------------------------------------------------------------------*/

#pragma once

#include "VariantBase.h"

namespace ursine
{
    namespace meta
    {
        class ArrayWrapper;

        template<typename T, typename StorageType>
        class ArrayVariantContainer : public VariantBase
        {
        public:
            ArrayVariantContainer(StorageType &rhs);

            Type GetType(void) const override;
            void *GetPtr(void) const override;

            int ToInt(void) const override;
            bool ToBool(void) const override;
            float ToFloat(void) const override;
            double ToDouble(void) const override;
            std::string ToString(void) const override;

            bool IsArray(void) const override;
            ArrayWrapper GetArray(void) const override;

            VariantBase *Clone(void) const override;

        private:
            StorageType m_array;
        };
    }
}

#include "Impl/ArrayVariantContainer.hpp"