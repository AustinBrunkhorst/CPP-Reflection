/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** Constructor.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaContainer.h"

#include "Invokable.h"

#include <functional>

namespace ursine
{
    namespace meta
    {
        class Type;

        class Constructor
            : public MetaContainer
            , public Invokable
        {
        public:
            typedef std::function<Variant(ArgumentList&)> Invoker;

            Constructor(void);
            
            Constructor(
                Type classType, 
                InvokableSignature signature, 
                Invoker invoker, 
                bool isDynamic
            );

            static const Constructor &Invalid(void);

            Type GetClassType(void) const;

            bool IsValid(void) const;
            bool IsDynamic(void) const;

            Variant InvokeVariadic(ArgumentList &arguments) const;

            template<typename ...Args>
            Variant Invoke(Args &&...args) const;

        private:
            bool m_isDynamic;

            Type m_classType;

            Invoker m_invoker;
        };
    }
}

#include "Impl/Constructor.hpp"