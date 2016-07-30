/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Destructor.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "Destructor.h"

#include "Variant.h"

#include "Common/Logging.h"

namespace ursine
{
    namespace meta
    {
        namespace
        {
            const auto kDestructorName = "destructor";
        }

        Destructor::Destructor(void)
            : Invokable( )
            , m_classType( Type::Invalid( ) ) { }

        Destructor::Destructor(Type classType, DestructorInvokerBase *invoker)
            : Invokable( kDestructorName )
            , m_classType( classType )
            , m_invoker( invoker ) { }

        Type Destructor::GetClassType(void) const
        {
            return m_classType;
        }

        void Destructor::Invoke(Variant &instance) const
        {
            UAssert( IsValid( ), 
                "Invalid constructor invoked." 
            );

            UAssert( m_classType == instance.GetType( ), 
                "Destructor called on incompatible type." 
            );
        
            m_invoker->Invoke( instance );

            delete instance.m_base;

            instance.m_base = nullptr;
        }

        const Destructor &Destructor::Invalid(void)
        {
            static Destructor invalid;

            return invalid;
        }

        bool Destructor::IsValid(void) const
        {
            return m_invoker != nullptr;
        }
    }
}