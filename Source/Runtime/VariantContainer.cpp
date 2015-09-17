#include "UrsinePrecompiled.h"

#include "VariantContainer.h"

#include "Type.h"

#include <algorithm>

namespace ursine
{
    namespace meta
    {
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 
        // void
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////

        #pragma region void

        VariantContainer<void>::VariantContainer(void) { }

        Type VariantContainer<void>::GetType(void) const
        {
            return typeof( void );
        }

        ///////////////////////////////////////////////////////////////////////

        void *VariantContainer<void>::GetPtr(void) const
        {
            return nullptr;
        }

        ///////////////////////////////////////////////////////////////////////

        int VariantContainer<void>::ToInt(void) const
        {
            return int( );
        }

        ///////////////////////////////////////////////////////////////////////

        bool VariantContainer<void>::ToBool(void) const
        {
            return bool( );
        }

        ///////////////////////////////////////////////////////////////////////

        float VariantContainer<void>::ToFloat(void) const
        {
            return float( );
        }

        ///////////////////////////////////////////////////////////////////////

        double VariantContainer<void>::ToDouble(void) const
        {
            return double( );
        }

        ///////////////////////////////////////////////////////////////////////

        std::string VariantContainer<void>::ToString(void) const
        {
            return std::string( );
        }

        ///////////////////////////////////////////////////////////////////////

        VariantBase *VariantContainer<void>::Clone(void) const
        {
            return new VariantContainer<void>( );
        }

        #pragma endregion

        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 
        // int
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 

        #pragma region int

        VariantContainer<int>::VariantContainer(const int &value)
            : m_value( value ) { }

        ///////////////////////////////////////////////////////////////////////

        VariantContainer<int>::VariantContainer(const int &&value)
            : m_value( std::move( value ) ) { }

        ///////////////////////////////////////////////////////////////////////

        Type VariantContainer<int>::GetType(void) const
        {
            return typeof( int );
        }

        ///////////////////////////////////////////////////////////////////////

        void *VariantContainer<int>::GetPtr(void) const
        {
            return const_cast<void*>(
                reinterpret_cast<const void*>(
                    std::addressof( m_value )
                )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        int VariantContainer<int>::ToInt(void) const
        {
            return m_value;
        }

        ///////////////////////////////////////////////////////////////////////

        bool VariantContainer<int>::ToBool(void) const
        {
            return m_value == 0 ? false : true;
        }

        ///////////////////////////////////////////////////////////////////////

        float VariantContainer<int>::ToFloat(void) const
        {
            return static_cast<float>( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        double VariantContainer<int>::ToDouble(void) const
        {
            return static_cast<double>( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        std::string VariantContainer<int>::ToString(void) const
        {
            return std::to_string( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        VariantBase *VariantContainer<int>::Clone(void) const
        {
            return new VariantContainer<int>( m_value );
        }

        #pragma endregion

        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 
        // bool
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 

        #pragma region bool

        VariantContainer<bool>::VariantContainer(const bool &value)
            : m_value( value ) { }

        ///////////////////////////////////////////////////////////////////////

        VariantContainer<bool>::VariantContainer(const bool &&value)
            : m_value( std::move( value ) ) { }

        ///////////////////////////////////////////////////////////////////////

        Type VariantContainer<bool>::GetType(void) const
        {
            return typeof( bool );
        }

        ///////////////////////////////////////////////////////////////////////

        void *VariantContainer<bool>::GetPtr(void) const
        {
            return const_cast<void*>(
                reinterpret_cast<const void*>(
                    std::addressof( m_value )
                )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        int VariantContainer<bool>::ToInt(void) const
        {
            return m_value ? 1 : 0;
        }

        ///////////////////////////////////////////////////////////////////////

        bool VariantContainer<bool>::ToBool(void) const
        {
            return m_value;
        }

        ///////////////////////////////////////////////////////////////////////

        float VariantContainer<bool>::ToFloat(void) const
        {
            return m_value ? 1.0f : 0.0f;
        }

        ///////////////////////////////////////////////////////////////////////

        double VariantContainer<bool>::ToDouble(void) const
        {
            return m_value ? 1.0 : 0.0;
        }

        ///////////////////////////////////////////////////////////////////////

        std::string VariantContainer<bool>::ToString(void) const
        {
            return m_value ? "true" : "false";
        }

        ///////////////////////////////////////////////////////////////////////

        VariantBase *VariantContainer<bool>::Clone(void) const
        {
            return new VariantContainer<bool>( m_value );
        }

        #pragma endregion

        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 
        // float
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 

        #pragma region float

        VariantContainer<float>::VariantContainer(const float &value)
            : m_value( value ) { }

        ///////////////////////////////////////////////////////////////////////

        VariantContainer<float>::VariantContainer(const float &&value)
            : m_value( std::move( value ) ) { }

        ///////////////////////////////////////////////////////////////////////

        Type VariantContainer<float>::GetType(void) const
        {
            return typeof( float );
        }

        ///////////////////////////////////////////////////////////////////////

        void *VariantContainer<float>::GetPtr(void) const
        {
            return const_cast<void*>(
                reinterpret_cast<const void*>(
                    std::addressof( m_value )
                )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        int VariantContainer<float>::ToInt(void) const
        {
            return static_cast<int>( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        bool VariantContainer<float>::ToBool(void) const
        {
            return m_value == 0.0f ? false : true;
        }

        ///////////////////////////////////////////////////////////////////////

        float VariantContainer<float>::ToFloat(void) const
        {
            return m_value;
        }

        ///////////////////////////////////////////////////////////////////////

        double VariantContainer<float>::ToDouble(void) const
        {
            return static_cast<double>( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        std::string VariantContainer<float>::ToString(void) const
        {
            return std::to_string( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        VariantBase *VariantContainer<float>::Clone(void) const
        {
            return new VariantContainer<float>( m_value );
        }

        #pragma endregion

        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 
        // double
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 

        #pragma region double

        VariantContainer<double>::VariantContainer(const double &value)
            : m_value( value ) { }

        ///////////////////////////////////////////////////////////////////////

        VariantContainer<double>::VariantContainer(const double &&value)
            : m_value( std::move( value ) ) { }

        ///////////////////////////////////////////////////////////////////////

        Type VariantContainer<double>::GetType(void) const
        {
            return typeof( double );
        }

        ///////////////////////////////////////////////////////////////////////

        void *VariantContainer<double>::GetPtr(void) const
        {
            return const_cast<void*>(
                reinterpret_cast<const void*>(
                    std::addressof( m_value )
                )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        int VariantContainer<double>::ToInt(void) const
        {
            return static_cast<int>( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        bool VariantContainer<double>::ToBool(void) const
        {
            return m_value == 0.0 ? false : true;
        }

        ///////////////////////////////////////////////////////////////////////

        float VariantContainer<double>::ToFloat(void) const
        {
            return static_cast<float>( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        double VariantContainer<double>::ToDouble(void) const
        {
            return m_value;
        }

        ///////////////////////////////////////////////////////////////////////

        std::string VariantContainer<double>::ToString(void) const
        {
            return std::to_string( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        VariantBase *VariantContainer<double>::Clone(void) const
        {
            return new VariantContainer<double>( m_value );
        }

        #pragma endregion

        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 
        // string
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////// 

        #pragma region string

        VariantContainer<std::string>::VariantContainer(
            const std::string &value
        )
            : m_value( value ) { }

        ///////////////////////////////////////////////////////////////////////

        VariantContainer<std::string>::VariantContainer(
            const std::string &&value
        )
            : m_value( std::move( value ) ) { }

        ///////////////////////////////////////////////////////////////////////

        Type VariantContainer<std::string>::GetType(void) const
        {
            return typeof( std::string );
        }

        ///////////////////////////////////////////////////////////////////////

        void *VariantContainer<std::string>::GetPtr(void) const
        {
            return const_cast<void*>(
                reinterpret_cast<const void*>(
                    std::addressof( m_value )
                )
            );
        }

        ///////////////////////////////////////////////////////////////////////

        int VariantContainer<std::string>::ToInt(void) const
        {
            return stoi( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        bool VariantContainer<std::string>::ToBool(void) const
        {
            // 0 -> false
            // 1 -> true
            // "true" -> true (case insensitive)
            // "false" -> false (case insensitive)

            if (m_value == "0")
                return false;

            if (m_value == "1")
                return true;

            auto copy = m_value;

            // convert to lowercase
            transform( copy.begin( ), copy.end( ), copy.begin( ), tolower );

            if (copy == "true")
                return true;

            return false;
        }

        ///////////////////////////////////////////////////////////////////////

        float VariantContainer<std::string>::ToFloat(void) const
        {
            return stof( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        double VariantContainer<std::string>::ToDouble(void) const
        {
            return stod( m_value );
        }

        ///////////////////////////////////////////////////////////////////////

        std::string VariantContainer<std::string>::ToString(void) const
        {
            return m_value;
        }

        ///////////////////////////////////////////////////////////////////////

        VariantBase *VariantContainer<std::string>::Clone(void) const
        {
            return new VariantContainer<std::string>( m_value );
        }

        #pragma endregion
    }
}
