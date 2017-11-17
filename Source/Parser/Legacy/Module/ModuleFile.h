/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ModuleFile.h
** --------------------------------------------------------------------------*/

#pragma once

class Class;
class Global;
class Function;
class Enum;

struct ModuleFile
{
    std::string name;

    std::vector<std::shared_ptr<Class>> classes;
    std::vector<std::shared_ptr<Global>> globals;
    std::vector<std::shared_ptr<Function>> globalFunctions;
    std::vector<std::shared_ptr<Enum>> enums;
};