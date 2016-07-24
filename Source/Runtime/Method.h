/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaContainer.h"

#include "Invokable.h"

#include "Variant.h"
#include "Argument.h"

#include "MethodInvoker.h"

#include <vector>
#include <unordered_map>
#include <functional>

namespace ursine
{
    namespace meta
    {
        class Method
            : public MetaContainer
            , public Invokable
        {
        public:
            Method(void);

            template<
                class ClassType, 
                typename ReturnType, 
                typename ...ArgTypes
            >
            Method(
                const std::string &name, 
                ReturnType(ClassType::*method)(ArgTypes...)
            );

            // detect const-ness
            template<
                class ClassType, 
                typename ReturnType, 
                typename ...ArgTypes
            >
            Method(
                const std::string &name, 
                ReturnType(ClassType::*method)(ArgTypes...) const
            );

            static const Method &Invalid(void);

            Type GetClassType(void) const;

            bool IsValid(void) const;
            bool IsConst(void) const;

            Variant Invoke(Variant &instance, ArgumentList &arguments) const;

            template<typename ...Args>
            Variant Invoke(Variant &instance, Args &&...args) const;

        private:
            bool m_isConst;

            Type m_classType;

            std::shared_ptr<MethodInvokerBase> m_invoker;
        };
    }
}

#include "Impl/Method.hpp"