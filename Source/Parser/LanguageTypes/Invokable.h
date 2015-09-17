#pragma once

#include "Cursor.h"
#include "Namespace.h"

class Invokable
{
public:
    typedef std::vector<std::string> Signature;

    Invokable(const Cursor &cursor);

protected:
    std::string m_returnType;

    Signature m_signature;

    TemplateData compileSignatureTemplate(void) const;
};

const auto kReturnTypeVoid = "void";