/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Method.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaContainer.h"

#include "Invokable.h"

#include "Variant.h"
#include "Argument.h"

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
            typedef std::function<Variant(Variant&, ArgumentList&)> Invoker;

            Method(void);

            template<
                class ClassType, 
                typename ReturnType, 
                typename ...ArgTypes
            >
            Method(
                const std::string &name, 
                ReturnType(ClassType::*method)(ArgTypes...), 
                Invoker invoker
            );

            // detect const-ness
            template<
                class ClassType, 
                typename ReturnType, 
                typename ...ArgTypes
            >
            Method(
                const std::string &name, 
                ReturnType(ClassType::*method)(ArgTypes...) const, 
                Invoker invoker
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

            Invoker m_invoker;
        };
    }
}

#include "Impl/Method.hpp"