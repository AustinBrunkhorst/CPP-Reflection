/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ArrayWrapperContainer.h
** --------------------------------------------------------------------------*/

#pragma once

#include "ArrayWrapperBase.h"

namespace ursine
{
    namespace meta
    {
        class Variant;
        class Argument;

        template<typename T>
        class ArrayWrapperContainer : public ArrayWrapperBase
        {
        public:
            ArrayWrapperContainer(Array<T> &a);

            Variant GetValue(size_t index) override;
            void SetValue(size_t index, const Argument &value) override;

            void Insert(size_t index, const Argument &value) override;
            void Remove(size_t index) override;

            size_t Size(void) const override;
            
        private:
            Array<T> &m_array;
        };
    }
}

#include "Impl/ArrayWrapperContainer.hpp"