/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Logging.h
** --------------------------------------------------------------------------*/

#pragma once

#define UAssert(assertion, ...) (!!(assertion) ||                                 \
    (ursine::logging::Assert(__FILE__, __FUNCTION__, __LINE__,##__VA_ARGS__), 0)) \

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
        );
    }
}

#include "Logging.hpp"