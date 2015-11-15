/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** ReflectionOptions.h
** --------------------------------------------------------------------------*/

#pragma once

struct ReflectionOptions
{
    std::string targetName;

    std::string inputSourceFile;

    std::string outputHeaderFile;
    std::string outputSourceFile;

    std::string precompiledHeader;

    std::string templateDirectory;

    std::vector<std::string> arguments;
};