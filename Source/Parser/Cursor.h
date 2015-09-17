#pragma once

#include "CursorType.h"

class Cursor
{
public:
    typedef std::vector<Cursor> List;
    typedef CXCursorVisitor Visitor;

    Cursor(const CXCursor &handle);

    CXCursorKind GetKind(void) const;

    Cursor GetLexicalParent(void) const;

    std::string GetSpelling(void) const;
    std::string GetDisplayName(void) const;
    std::string GetMangledName(void) const;

    bool IsDefinition(void) const;
    bool IsConst(void) const;
    bool IsStatic(void) const;

    CX_CXXAccessSpecifier GetAccessModifier(void) const;
    CX_StorageClass GetStorageClass(void) const;

    CursorType GetType(void) const;
    CursorType GetReturnType(void) const;
    CursorType GetTypedefType(void) const;

    List GetChildren(void) const;
    void VisitChildren(Visitor visitor, void *data = nullptr);

private:
    CXCursor m_handle;
};