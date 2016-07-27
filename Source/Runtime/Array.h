/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ArrayConfig.h
** --------------------------------------------------------------------------*/

#pragma once

#include <vector>

namespace ursine
{
    // Basic wrapper around std::vector. Clang has a hard time with other 
    // compilers implementation of std::vector, so this must be used in order to have 
    // Array like functionality within the runtime
    template<typename T>
    class Array : public std::vector<T>
    {
    public:
        Array(void);
        Array(const std::vector<T> &rhs);
        Array(const std::vector<T> &&rhs);
        Array(const std::initializer_list<T> &rhs);
        Array(const std::initializer_list<T> &&rhs);
    };
}

#include "Impl/Array.hpp"