/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Variant.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "Variant.h"

#include "Type.h"

namespace ursine
{
    namespace meta
    {
        Variant::Variant(void)
            : m_isConst( true )
            , m_base( nullptr ) { }

        Variant::Variant(const Variant &rhs)
            : m_isConst( rhs.m_isConst )
            , m_base( rhs.m_base ? rhs.m_base->Clone( ) : nullptr ) { }

        Variant::Variant(Variant &&rhs)
            : m_isConst( rhs.m_isConst )
            , m_base( rhs.m_base )
        {
            rhs.m_isConst = true;
            rhs.m_base = nullptr;
        }

        Variant::~Variant(void)
        {
            delete m_base;
        }

        Variant &Variant::operator=(const Variant &rhs)
        {
            Variant( rhs ).Swap( *this );

            return *this;
        }

        Variant &Variant::operator=(Variant &&rhs)
        {
            rhs.Swap( *this );

            Variant( ).Swap( rhs );

            return *this;
        }

        Variant::operator bool(void) const 
        {
            return m_base != nullptr;
        }

        Type Variant::GetType(void) const
        {
            return m_base ? m_base->GetType( ) : Type::Invalid( );
        }

        ArrayWrapper Variant::GetArray(void) const
        {
            return m_base ? m_base->GetArray( ) : ArrayWrapper( );
        }

        int Variant::ToInt(void) const
        {
            return m_base ? m_base->ToInt( ) : int( );
        }

        bool Variant::ToBool(void) const
        {
            return m_base ? m_base->ToBool( ) : bool( );
        }

        float Variant::ToFloat(void) const
        {
            return m_base ? m_base->ToFloat( ) : float( );
        }

        double Variant::ToDouble(void) const
        {
            return m_base ? m_base->ToDouble( ) : double( );
        }

        std::string Variant::ToString(void) const
        {
            return m_base ? m_base->ToString( ) : std::string( );
        }

        Json Variant::SerializeJson(void) const
        {
            return GetType( ).SerializeJson( *this );
        }

        void Variant::Swap(Variant &other)
        {
            std::swap( m_base, other.m_base );
        }

        bool Variant::IsValid(void) const
        {
            return m_base != nullptr;
        }

        bool Variant::IsConst(void) const
        {
            return m_isConst;
        }

        bool Variant::IsArray(void) const
        {
            return m_base ? m_base->IsArray( ) : false;
        }

        void *Variant::getPtr(void) const
        {
            return m_base ? m_base->GetPtr( ) : nullptr;
        }
    }
}
