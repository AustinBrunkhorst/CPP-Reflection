/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** EnumContainer.h
** --------------------------------------------------------------------------*/

#pragma once

#include "EnumBase.h"

#include "Variant.h"

#include <unordered_map>

namespace ursine
{
    namespace meta
    {
        template<typename EnumType>
        class EnumContainer : public EnumBase
        {
        public:
            typedef std::unordered_map<std::string, EnumType> Table;

            EnumContainer(const std::string &name, const Table &table);
            
            EnumContainer(
                const std::string &name, 
                const Table &table, 
                TypeID owner
            );

            Type GetType(void) const override;
            Type GetUnderlyingType(void) const override;

            std::vector<std::string> GetKeys(void) const override;
            std::vector<Variant> GetValues(void) const override;

            std::string GetKey(const Argument &value) const override;
            Variant GetValue(const std::string &key) const override;

        private:
            Table m_table;
        };
    }
}

#include "Impl/EnumContainer.hpp"