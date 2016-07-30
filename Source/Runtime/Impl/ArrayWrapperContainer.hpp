/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ArrayWrapperContainer.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "../Argument.h"
#include "../Variant.h"

namespace ursine
{
    namespace meta
    {
        template<typename T>
        ArrayWrapperContainer<T>::ArrayWrapperContainer(Array<T> &a)
            : m_array( a )
        {

        }

        template<typename T>
        Variant ArrayWrapperContainer<T>::GetValue(size_t index)
        {
            return { m_array[ index ] };
        }

        template<typename T>
        void ArrayWrapperContainer<T>::SetValue(size_t index, const Argument &value)
        {
            m_array.at( index ) = value.GetValue<T>( );
        }

        template<typename T>
        void ArrayWrapperContainer<T>::Insert(size_t index, const Argument &value)
        {
            m_array.insert( m_array.begin( ) + index, value.GetValue<T>( ) );
        }

        template<typename T>
        void ArrayWrapperContainer<T>::Remove(size_t index)
        {
            m_array.erase( m_array.begin( ) + index );
        }

        template<typename T>
        size_t ArrayWrapperContainer<T>::Size(void) const
        {
            return m_array.size( );
        }
    }
}