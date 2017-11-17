/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaUtils.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Cursor.h"
#include "Namespace.h"

#include "Mustache.h"

namespace utils
{
    void ToString(const CXString &str, std::string &output);

    Mustache::Data<std::string>::Type TemplateBool(bool value);

    std::string GetQualifiedName(const CursorType &type);

    std::string GetQualifiedName(
        const std::string &displayName, 
        const Namespace &currentNamespace
    );

    std::string GetQualifiedName(
        const Cursor &cursor, 
        const Namespace &currentNamespace
    );

    void LoadText(const std::string &filename, std::string &output);
    void WriteText(const std::string &filename, const std::string &text);

    boost::filesystem::path MakeRelativePath(
        const boost::filesystem::path &from, 
        const boost::filesystem::path &to
    );

    void FatalError(const std::string &error);

    template<typename A, typename B>
    bool RangeEqual(A startA, A endA, B startB, B endB);
}

#include "MetaUtils.hpp"