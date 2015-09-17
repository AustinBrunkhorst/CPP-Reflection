/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Precompiled.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <functional>

#include <clang-c/Index.h>

#include <MacroUtils.h>
#include <UrsineLogTools.h>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "MetaUtils.h"
#include "MetaDataConfig.h"

#include "Mustache.h"

using MustacheTemplate = Mustache::Mustache<std::string>;
using TemplateData = Mustache::Data<std::string>;

namespace fs = boost::filesystem;
namespace po = boost::program_options;