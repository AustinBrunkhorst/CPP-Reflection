/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaManager.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaProperty.h"

#include "JsonConfig.h"

#include <string>
#include <map>
#include <vector>

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

            typedef std::vector<Variant> PropertyList;

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

            // Gets all properties
            PropertyList GetProperties(void) const;

            Json SerializeJson(void) const;

        private:
            void copy(const MetaManager &rhs);

            std::map<Type, const MetaProperty *> m_properties;
        };
    }
}

#include "Impl/MetaManager.hpp"