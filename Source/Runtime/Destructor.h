/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Destructor.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Invokable.h"

#include "DestructorInvoker.h"

namespace ursine
{
    namespace meta
    {
        class Destructor : public Invokable
        {
        public:
            Destructor(void);
            Destructor(Type classType, DestructorInvokerBase *invoker);

            static const Destructor &Invalid(void);

            Type GetClassType(void) const;

            bool IsValid(void) const;

            void Invoke(Variant &instance) const;

        private:
            Type m_classType;

            std::shared_ptr<DestructorInvokerBase> m_invoker;
        };
    }
}