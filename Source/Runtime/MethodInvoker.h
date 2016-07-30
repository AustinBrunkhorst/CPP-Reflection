/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MethodInvoker.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MethodInvokerBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, typename ReturnType, typename ...ArgTypes>
        class MethodInvoker : public MethodInvokerBase
        {
        public:
            typedef ReturnType (ClassType::*Signature)(ArgTypes...);
            typedef ReturnType (ClassType::*ConstSignature)(ArgTypes...) const;

            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Method has too many arguments. It's time to generate more overloads." 
            );

            MethodInvoker(Signature method);
            MethodInvoker(ConstSignature method);

            Variant Invoke(Variant &obj, const ArgumentList &arguments) override;

        private:
            template<typename _>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            Variant invoke(Variant &obj, const ArgumentList &arguments);

            ConstSignature m_method;
        };
    }
}

#include "Impl/MethodInvoker.hpp"
#include "Impl/VoidMethodInvoker.hpp"