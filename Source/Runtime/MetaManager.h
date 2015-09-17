/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** MetaManager.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaProperty.h"

#include <string>
#include <map>

namespace ursine
{
    namespace meta
    {
        class Type;
        class Variant;

        class MetaManager
        {
        public:
            typedef std::initializer_list<
                std::pair<Type, const MetaProperty *>
            > Initializer;

            MetaManager(void);
            MetaManager(const MetaManager &rhs);
            MetaManager(const MetaManager &&rhs);

            const MetaManager &operator=(const MetaManager &rhs);

            MetaManager(const Initializer &properties);

            ~MetaManager(void);

            Variant GetProperty(Type type) const;

            template<typename PropertyType>
            const PropertyType *GetProperty(void) const;

            // Sets the given property
            void SetProperty(Type type, const MetaProperty *value);

        private:
            void copy(const MetaManager &rhs);

            std::map<Type, const MetaProperty *> m_properties;
        };
    }
}

#include "Impl/MetaManager.hpp"