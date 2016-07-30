/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Function.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaContainer.h"
#include "Invokable.h"

#include "Variant.h"
#include "Argument.h"

#include "FunctionInvoker.h"

#include <functional>

namespace ursine
{
    namespace meta
    {
        class Function
            : public MetaContainer
            , public Invokable
        {
        public:
            typedef std::function<Variant(ArgumentList&)> Invoker;

            Function(void);

            template<typename ReturnType, typename ...ArgTypes>
            Function(
                const std::string &name, 
                ReturnType (*function)(ArgTypes...),
                Type parentType = Type::Invalid( )
            );

            static const Function &Invalid(void);

            Type GetParentType(void) const;

            bool IsValid(void) const;

            Variant InvokeVariadic(ArgumentList &arguments) const;

            template<typename ...Args>
            Variant Invoke(Args &&...args) const;

        private:
            Type m_parentType;

            std::shared_ptr<FunctionInvokerBase> m_invoker;
        };
    }
}

#include "Impl/Function.hpp"