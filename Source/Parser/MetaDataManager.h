/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** MetaDataManager.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "Cursor.h"

class ReflectionParser;

class MetaDataManager
{
public:
    MetaDataManager(const Cursor &cursor);

    std::string GetProperty(const std::string &key) const;
    bool GetFlag(const std::string &key) const;

    std::string GetNativeString(const std::string &key) const;

    void CompileTemplateData(
    	TemplateData &data, 
    	const ReflectionParser *context
	) const;
private:
    typedef std::pair<std::string, std::string> Property;

    std::unordered_map<std::string, std::string> m_properties;

    std::vector<Property> extractProperties(const Cursor &cursor) const;
};