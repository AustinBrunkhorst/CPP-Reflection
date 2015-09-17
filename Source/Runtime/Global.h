/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Global.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaContainer.h"

#include "Variant.h"

#include <vector>
#include <functional>

namespace ursine
{
    namespace meta
    {
        class Global : public MetaContainer
        {
        public:
            typedef std::function<Variant(void)> Getter;
            typedef std::function<void(const Argument &)> Setter;

            Global(void);

            Global(
                const std::string &name, 
                Type type, 
                Getter getter, 
                Setter setter, 
                Type parentType = Type::Invalid
            );

            bool IsValid(void) const;
            bool IsReadOnly(void) const;

            Type GetType(void) const;
            Type GetParentType(void) const;

            const std::string &GetName(void) const;

            Variant GetValue(void) const;
            bool SetValue(const Argument &value) const;
            
        private:
            Type m_type;
            Type m_parentType;

            std::string m_name;

            Getter m_getter;
            Setter m_setter;
        };
    }
}