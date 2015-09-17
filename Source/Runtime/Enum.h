/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Enum.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "EnumBase.h"

namespace ursine
{
    namespace meta
    {
        class Enum
        {
        public:
            bool IsValid(void) const;

            operator bool(void) const;

            bool operator ==(const Enum &rhs) const;
            bool operator !=(const Enum &rhs) const;

            std::string GetName(void) const;

            Type GetType(void) const;
            Type GetParentType(void) const;
            Type GetUnderlyingType(void) const;

            std::vector<std::string> GetKeys(void) const;
            std::vector<Variant> GetValues(void) const;

            std::string GetKey(const Argument &value) const;
            Variant GetValue(const std::string &key) const;

        private:
            friend struct TypeData;

            Enum(const EnumBase *base);

            const EnumBase *m_base;
        };
    }
}