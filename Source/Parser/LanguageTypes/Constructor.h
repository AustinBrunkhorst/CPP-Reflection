#pragma once

#include "LanguageType.h"
#include "Invokable.h"

class Class;

class Constructor 
    : public LanguageType
    , public Invokable
{
public:
    Constructor(
    	const Cursor &cursor, 
    	const Namespace &currentNamespace, 
    	Class *parent = nullptr
	);

    virtual ~Constructor(void) { } 

    bool ShouldCompile(void) const;
    
    TemplateData CompileTemplate(
    	const ReflectionParser *context
	) const override;

private:
    Class *m_parent;

    bool isAccessible(void) const;

    std::string getTemplateParameters(void) const;
};