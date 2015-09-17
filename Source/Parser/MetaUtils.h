/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** MetaUtils.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "Cursor.h"
#include "Namespace.h"

#include "Mustache.h"

namespace utils
{
    void ToString(const CXString &str, std::string &output);

    Mustache::Data<std::string>::Type TemplateBool(bool value);

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

    void FatalError(const std::string &error);
}