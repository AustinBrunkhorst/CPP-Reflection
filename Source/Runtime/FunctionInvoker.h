/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** FunctionInvoker.h
** --------------------------------------------------------------------------*/

#pragma once

#include "FunctionInvokerBase.h"

namespace ursine
{
    namespace meta
    {
        template<typename ReturnType, typename ...ArgTypes>
        class FunctionInvoker : public FunctionInvokerBase
        {
        public:
            typedef ReturnType (*Signature)(ArgTypes...);

            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Function has too many arguments. It's time to generate more overloads." 
            );

            FunctionInvoker(Signature function);

            Variant Invoke(const ArgumentList &arguments) override;

        private:
            template<typename _>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            Variant invoke(const ArgumentList &arguments);

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            Variant invoke(const ArgumentList &arguments);

            Signature m_function;
        };
    }
}

#include "Impl/FunctionInvoker.hpp"
#include "Impl/VoidFunctionInvoker.hpp"