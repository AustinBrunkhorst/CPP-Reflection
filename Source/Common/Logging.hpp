/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Logging.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include <iostream>

namespace ursine
{
    namespace logging
    {
        template<typename... Args>
        void Assert(
            const std::string &file,
            const std::string &function,
            unsigned line,
            const std::string &format,
            const Args&... args
        )
        {
            std::cerr << "----- Assertion Failed -----" << std::endl
                      << "----------------------------" << std::endl;

            std::fprintf( stderr, format.c_str( ), args... );

            std::cerr << std::endl;
            std::cerr << "----------------------------" << std::endl;
            std::cerr << "file: " << file << std::endl;
            std::cerr << "function: " << function << std::endl;
            std::cerr << "line: " << line << std::endl;
            std::cerr << "----------------------------" << std::endl;
            std::cerr << std::endl;

            std::abort( );
        }
    }
}