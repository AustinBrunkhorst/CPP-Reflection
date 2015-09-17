/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** ReflectionParser.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "ReflectionOptions.h"

#include "Cursor.h"
#include "Namespace.h"

#include "Templates.h"

class Class;
class Global;
class Function;
class Enum;

class ReflectionParser
{
public:
    ReflectionParser(const ReflectionOptions &options);
    ~ReflectionParser(void);

    void Parse(void);

    MustacheTemplate LoadTemplate(const std::string &name) const;

    TemplateData::PartialType LoadTemplatePartial(
        const std::string &name
    ) const;

    void GenerateHeader(std::string &output) const;
    void GenerateSource(std::string &output) const;

private:
    ReflectionOptions m_options;

    CXIndex m_index;
    CXTranslationUnit m_translationUnit;

    std::vector<Class*> m_classes;
    std::vector<Global*> m_globals;
    std::vector<Function*> m_globalFunctions;
    std::vector<Enum*> m_enums;

    mutable std::unordered_map<
        std::string, 
        std::string
    > m_templatePartialCache;

    void buildClasses(const Cursor &cursor, Namespace &currentNamespace);
    void buildGlobals(const Cursor &cursor, Namespace &currentNamespace);

    void buildGlobalFunctions(
        const Cursor &cursor, 
        Namespace &currentNamespace
    );

    void buildEnums(const Cursor &cursor, Namespace &currentNamespace);

    TemplateData compileClassTemplates(void) const;
    TemplateData compileGlobalTemplates(void) const;
    TemplateData compileGlobalFunctionTemplates(void) const;
    TemplateData compileEnumTemplates(void) const;
};