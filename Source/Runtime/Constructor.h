/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Constructor.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaContainer.h"
#include "Invokable.h"

#include "Type.h"

#include "ConstructorInvoker.h"

#include <memory>

namespace ursine
{
    namespace meta
    {
        class Variant;
        class Argument;

        class Constructor
            : public MetaContainer
            , public Invokable
        {
        public:
            Constructor(void);
            Constructor(const Constructor &rhs);
            Constructor(const Constructor &&rhs);
            
            Constructor(
                Type classType, 
                InvokableSignature signature, 
                ConstructorInvokerBase *invoker, 
                bool isDynamic
            );

            Constructor &operator=(const Constructor &&rhs);

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

            std::shared_ptr<ConstructorInvokerBase> m_invoker;
        };
    }
}

#include "Impl/Constructor.hpp"