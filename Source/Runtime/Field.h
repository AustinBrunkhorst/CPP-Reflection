/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Field.h
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
        class Field : public MetaContainer
        {
        public:
            typedef std::function<Variant(const Variant &)> Getter;
            typedef std::function<void(Variant &, const Variant &)> Setter;

            Field(void);

            Field(
                const std::string &name, 
                Type type, 
                Type classType, 
                Getter getter, 
                Setter setter
            );

            bool IsValid(void) const;
            bool IsReadOnly(void) const;

            Type GetType(void) const;
            Type GetClassType(void) const;

            const std::string &GetName(void) const;

            Variant GetValue(Variant &instance) const;
            bool SetValue(Variant &instance, const Variant &value) const;
            
        private:
            Type m_type;
            Type m_classType;

            std::string m_name;

            Getter m_getter;
            Setter m_setter;
        };
    }
}