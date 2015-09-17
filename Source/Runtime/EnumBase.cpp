#include "UrsinePrecompiled.h"

#include "EnumBase.h"

#include "Variant.h"
#include "Argument.h"

namespace ursine
{
    namespace meta
    {
        EnumBase::EnumBase(const std::string &name, TypeID owner)
            : m_parentType( owner )
            , m_name( name ) { }

        Type EnumBase::GetParentType(void) const
        {
            return m_parentType;
        }

        const std::string &EnumBase::GetName(void) const
        {
            return m_name;
        }
    }
}