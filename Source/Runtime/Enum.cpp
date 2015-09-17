#include "UrsinePrecompiled.h"

#include "Enum.h"

#include "Variant.h"

namespace ursine
{
    namespace meta
    {
        Enum::Enum(const EnumBase *base)
            : m_base( base ) { }

        bool Enum::IsValid(void) const
        {
            return m_base != nullptr;
        }

        Enum::operator bool(void) const
        {
            return m_base != nullptr;
        }

        bool Enum::operator==(const Enum &rhs) const
        {
            return m_base == rhs.m_base;
        }

        bool Enum::operator!=(const Enum &rhs) const
        {
            return m_base != rhs.m_base;
        }

        std::string Enum::GetName(void) const
        {
            return m_base ? m_base->GetName( ) : std::string( );
        }

        Type Enum::GetType(void) const
        {
            return m_base ? m_base->GetType( ) : Type::Invalid;
        }

        Type Enum::GetParentType(void) const
        {
            return m_base ? m_base->GetParentType( ) : Type::Invalid;
        }

        Type Enum::GetUnderlyingType(void) const
        {
            return m_base ? m_base->GetUnderlyingType( ) : Type::Invalid;
        }

        std::vector<std::string> Enum::GetKeys(void) const
        {
            return m_base ? m_base->GetKeys( ) : std::vector<std::string>( );
        }

        std::vector<Variant> Enum::GetValues(void) const
        {
            return m_base ? m_base->GetValues( ) : std::vector<Variant>( );
        }

        std::string Enum::GetKey(const Argument &value) const
        {
            return m_base ? m_base->GetKey( value ) : std::string( );
        }

        Variant Enum::GetValue(const std::string &key) const
        {
            return m_base ? m_base->GetValue( key ) : Variant( );
        }
    }
}
