/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Variant.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "../VariantContainer.h"
#include "../ObjectWrapper.h"
#include "../ArrayVariantContainer.h"

namespace ursine
{
    namespace meta
    {
        template <typename T>
        Variant::Variant(
            T *data, 
            variant_policy::WrapObject, 
            typename std::enable_if< 
                std::is_base_of<Object, T>::value 
            >::type*
        )
            : m_isConst( std::is_const<T>::value )
            , m_base( 
                new ObjectWrapper( 
                    static_cast<Object *>( 
                        const_cast< typename std::remove_const<T>::type*>(
                            data 
                        )
                    ) 
                ) 
            )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(
            T &data,
            DISABLE_VARIANT
        )
            : m_isConst( std::is_pointer<T>::value && std::is_const<T>::value )
            , m_base( new VariantContainer< CleanedType<T> >( data ) )
        {
        
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(
            T &data,
            variant_policy::NoCopy,
            DISABLE_VARIANT
        )
            : m_isConst( std::is_pointer<T>::value && std::is_const<T>::value )
            , m_base( new VariantContainer< CleanedType<T>& >( data ) )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(
            T &&data,
            DISABLE_VARIANT,
            DISABLE_ARGUMENT,
            DISABLE_CONST
        )
            : m_isConst( false )
            , m_base( 
                new VariantContainer< CleanedType<T> >( 
                    static_cast<T&&>( data ) 
                )
            )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(Array<T> &rhs)
            : m_isConst( false )
            , m_base( new ArrayVariantContainer<T, meta_traits::ArrayByReference<T>>( rhs ) )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(const Array<T> &rhs)
            : m_isConst( true )
            , m_base( new ArrayVariantContainer<T, const meta_traits::ArrayByReference<T>>( const_cast<const meta_traits::ArrayByReference<T>>( rhs ) ) )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(Array<T> &&rhs)
            : m_isConst( false )
            , m_base( new ArrayVariantContainer<T, meta_traits::ArrayByValue<T>>( rhs ) )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(const Array<T> &&rhs)
            : m_isConst( true )
            , m_base( new ArrayVariantContainer<T, const meta_traits::ArrayByValue<T>>( rhs ) )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant &Variant::operator=(T &&rhs)
        {
            Variant( static_cast<T&&>( rhs ) ).Swap( *this );

            return *this;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        T &Variant::GetValue(void) const
        {
            return *static_cast<T*>( getPtr( ) );
        }
    }
}
