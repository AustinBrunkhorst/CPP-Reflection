#pragma once

#include "LanguageType.h"

#include "LanguageTypes/Constructor.h"
#include "LanguageTypes/Field.h"
#include "LanguageTypes/Global.h"
#include "LanguageTypes/Method.h"
#include "LanguageTypes/Function.h"

struct BaseClass
{
    BaseClass(const Cursor &cursor);

    std::string name;
};

class Class : public LanguageType
{
    // to access m_qualifiedName
    friend class Global;
    friend class Function;
    friend class Method;
    friend class Constructor;
    friend class Field;

public:
    Class(const Cursor &cursor, const Namespace &currentNamespace);
    virtual ~Class(void);

    bool ShouldCompile(void) const;

    TemplateData CompileTemplate(
        const ReflectionParser *context
    ) const override;
    
private:
    std::string m_name;
    std::string m_displayName;
    std::string m_qualifiedName;

    std::vector<BaseClass*> m_baseClasses;
        
    std::vector<Constructor*> m_constructors;

    std::vector<Field*> m_fields;
    std::vector<Global*> m_staticFields;

    std::vector<Method*> m_methods;
    std::vector<Function*> m_staticMethods;

    bool isAccessible(void) const;
};
