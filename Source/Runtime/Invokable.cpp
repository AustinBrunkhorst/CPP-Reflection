#include "UrsinePrecompiled.h"

#include "Invokable.h"

namespace ursine
{
    namespace meta
    {
        Invokable::Invokable(const std::string &name) 
            : m_name( name ) { }

        const InvokableSignature &Invokable::GetSignature(void) const
        {
            return m_signature;
        }

        const std::string &Invokable::GetName(void) const
        {
            return m_name;
        }
    }
}
