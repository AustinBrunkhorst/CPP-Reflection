#pragma once

#include "LanguageType.h"

#include "LanguageTypes/Global.h"

class Enum : public LanguageType
{
public:
    struct Value
    {
        Value(Enum *parent, const Cursor &cursor);

        std::string key;
        std::string value;
    };

    friend struct Value;

    Enum(const Cursor &cursor, const Namespace &currentNamespace);
    virtual ~Enum(void) { }

    bool ShouldCompile(void) const;
    
    TemplateData CompileTemplate(
        const ReflectionParser *context
    ) const override;

    static void LoadAnonymous(
        std::vector<Global*> &output, 
        const Cursor &cursor, 
        const Namespace &currentNamespace
    );

private:
    std::string m_name;
    std::string m_displayName;
    std::string m_qualifiedName;

    std::vector<Value> m_values;

    bool isAccessible(void) const;
};