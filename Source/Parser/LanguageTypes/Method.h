#pragma once

#include "LanguageType.h"
#include "Invokable.h"

class Class;

class Method 
    : public LanguageType
    , public Invokable
{
public:
    Method(
        const Cursor &cursor, 
        const Namespace &currentNamespace, 
        Class *parent = nullptr
    );

    virtual ~Method(void) { }

    bool ShouldCompile(void) const;
    
    TemplateData CompileTemplate(
        const ReflectionParser *context
    ) const override;

private:
    bool m_isConst;

    Class *m_parent;

    std::string m_name;

    bool isAccessible(void) const;

    std::string getQualifiedSignature(void) const;
};