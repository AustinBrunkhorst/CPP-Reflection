/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** ReflectionOptions.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
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