/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Constructor.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "Constructor.h"
#include "Invokable.h"
#include "Type.h"

#include "Common/Logging.h"

namespace ursine
{
    namespace meta
    {
        namespace
        {
            const auto kConstructorName = "constructor";
        }

        Constructor::Constructor(void)
            : Invokable( )
            , m_isDynamic( false )
            , m_classType( InvalidTypeID )
            , m_invoker( nullptr ) { }

        Constructor::Constructor(const Constructor &rhs)
            : Invokable( kConstructorName )
            , m_isDynamic( rhs.m_isDynamic )
            , m_classType( rhs.m_classType )
            , m_invoker( rhs.m_invoker )
        {
            m_signature = rhs.m_signature;
        }

        Constructor::Constructor(const Constructor &&rhs)
            : Invokable( kConstructorName )
            , m_isDynamic( rhs.m_isDynamic )
            , m_classType( rhs.m_classType )
            , m_invoker( std::move( rhs.m_invoker ) )
        {
            m_signature = std::move( rhs.m_signature );
        }

        Constructor::Constructor(
            Type classType, 
            InvokableSignature signature, 
            ConstructorInvokerBase *invoker,
            bool isDynamic
        )
            : Invokable( kConstructorName )
            , m_isDynamic( isDynamic )
            , m_classType( classType )
            , m_invoker( invoker )
        {
            m_signature = signature;
        }

        Constructor &Constructor::operator=(const Constructor &&rhs)
        {
            m_isDynamic = rhs.m_isDynamic;
            m_classType= rhs.m_classType;
            m_invoker = std::move( rhs.m_invoker );

            m_signature = std::move( rhs.m_signature );

            return *this;
        }

        const Constructor &Constructor::Invalid(void)
        {
            static Constructor invalid;

            return invalid;
        }

        Type Constructor::GetClassType(void) const
        {
            return m_classType;
        }

        bool Constructor::IsValid(void) const
        {
            return m_invoker != nullptr;
        }

        bool Constructor::IsDynamic(void) const
        {
            return m_isDynamic;
        }

        Variant Constructor::InvokeVariadic(ArgumentList &arguments) const
        {
            UAssert( IsValid( ), "Invalid constructor invoked." );

            return m_invoker->Invoke( arguments );
        }
    }
}
