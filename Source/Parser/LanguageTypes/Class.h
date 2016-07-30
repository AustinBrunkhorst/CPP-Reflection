/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Class.h
** --------------------------------------------------------------------------*/

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

    virtual bool ShouldCompile(void) const;

    TemplateData CompileTemplate(
        const ReflectionParser *context
    ) const override;
    
private:
    std::string m_name;
    std::string m_displayName;
    std::string m_qualifiedName;

    template<typename T>
    using SharedPtrVector = std::vector<std::shared_ptr<T>>;

    SharedPtrVector<BaseClass> m_baseClasses;

    SharedPtrVector<Constructor> m_constructors;

    SharedPtrVector<Field> m_fields;
    SharedPtrVector<Global> m_staticFields;

    SharedPtrVector<Method> m_methods;
    SharedPtrVector<Function> m_staticMethods;

    bool isAccessible(void) const;
};
