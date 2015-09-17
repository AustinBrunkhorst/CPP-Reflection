/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Switches.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include <string>

#define DEFINE_SWITCH(name, value)                   \
    const std::string kSwitch##name = value;         \
    const std::string kSwitch##name##Shorthand = ""; \

#define DEFINE_SWITCH_FULL(name, value, shorthand)              \
    const std::string kSwitch##name = value;                    \
    const std::string kSwitch##name##Shorthand = "," shorthand; \

#define SWITCH_OPTION(name)                                 \
    ((kSwitch##name) + (kSwitch##name##Shorthand)).c_str( ) \

DEFINE_SWITCH_FULL( Help,              "help",           "h" );
DEFINE_SWITCH_FULL( TargetName,        "target-name",    "t" );
DEFINE_SWITCH_FULL( InputSource,       "in-source",      "i" );
DEFINE_SWITCH_FULL( OutputHeader,      "out-header",     "a" );
DEFINE_SWITCH_FULL( OutputSource,      "out-source",     "b" );
DEFINE_SWITCH_FULL( TemplateDirectory, "tmpl-directory", "d" );
DEFINE_SWITCH_FULL( PrecompiledHeader, "pch",            "p" );
DEFINE_SWITCH_FULL( CompilerFlags,     "flags",          "f" );
