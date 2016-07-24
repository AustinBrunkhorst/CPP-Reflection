/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionOptions.h
** --------------------------------------------------------------------------*/

#pragma once

struct ReflectionOptions
{
    bool forceRebuild;
    bool displayDiagnostics;

    std::string targetName;

    std::string sourceRoot;
    std::string inputSourceFile;
    std::string moduleHeaderFile;

    std::string outputModuleSource;
    std::string outputModuleFileDirectory;

    std::string precompiledHeader;

    std::string templateDirectory;

    std::vector<std::string> arguments;
};