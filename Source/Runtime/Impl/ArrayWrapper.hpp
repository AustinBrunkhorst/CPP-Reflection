/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ArrayWrapper.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "../ArrayWrapperContainer.h"

namespace ursine
{
    namespace meta
    {
        template<typename T>
        ArrayWrapper::ArrayWrapper(Array<T> &rhs)
            : m_isConst( false )
            , m_base( new ArrayWrapperContainer<T>( rhs ) )
        {
            
        }

        template<typename T>
        ArrayWrapper::ArrayWrapper(const Array<T> &rhs)
            : m_isConst( true )
            , m_base( new ArrayWrapperContainer<T>( const_cast<Array<T> &>( rhs ) ) )
        {
            
        }
    }
}
