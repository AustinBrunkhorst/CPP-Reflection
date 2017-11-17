/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** LanguageType.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Cursor.h"
#include "Namespace.h"

#include "MetaDataManager.h"
#include "ReflectionParser.h"

class LanguageType
{
public:
    LanguageType(const Cursor &cursor, const Namespace &currentNamespace);
    virtual ~LanguageType(void) { }

    const MetaDataManager &GetMetaData(void) const;

    std::string GetSourceFile(void) const;

    virtual TemplateData CompileTemplate(
        const ReflectionParser *context
    ) const = 0;

protected:
    MetaDataManager m_metaData;

    // determines if the type is enabled in reflection database generation
    bool m_enabled;

    // determines if the pointer type to this type will be generated
    // in the reflection database
    bool m_ptrTypeEnabled;

    // determines if the constant pointer type to this type will be
    // generated in the reflection database
    bool m_constPtrTypeEnabled;

    // determines if this type generates data for its respective array type
    bool m_arrayTypeEnabled;

    CX_CXXAccessSpecifier m_accessModifier;

private:
    // cursor that represents the root of this language type
    Cursor m_rootCursor;
};