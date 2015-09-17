/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** ObjectWrapper.h
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

        private:
            Object *m_object;
        };
    }
}