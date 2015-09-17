/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** VariantContainer.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "VariantBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename T>
        class VariantContainer : public VariantBase
        {
        public:
            VariantContainer(const T &value);
            VariantContainer(const T &&value);

            Type GetType(void) const override;

            void *GetPtr(void) const override;

            int ToInt(void) const override;
            bool ToBool(void) const override;
            float ToFloat(void) const override;
            double ToDouble(void) const override;
            std::string ToString(void) const override;

            VariantBase *Clone(void) const override;

        private:
            friend class Variant;

            VariantContainer &operator=(const VariantContainer &rhs) = delete;

            T m_value;
        };
    }
}

#include "Impl/VariantContainer.hpp"
#include "Impl/VariantContainerStandardTypes.hpp"