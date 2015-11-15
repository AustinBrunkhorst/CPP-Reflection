/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** Destructor.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Invokable.h"

#include <functional>

namespace ursine
{
    namespace meta
    {
        class Destructor : public Invokable
        {
        public:
            typedef std::function<void(Variant &)> Invoker;

            Destructor(void);
            Destructor(Type classType, Invoker invoker);

            static const Destructor &Invalid(void);

            Type GetClassType(void) const;

            bool IsValid(void) const;

            void Invoke(Variant &instance) const;

        private:
            Type m_classType;

            Invoker m_invoker;
        };
    }
}

#include "Impl/Destructor.hpp"