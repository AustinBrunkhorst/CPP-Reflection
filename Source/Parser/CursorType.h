/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** CursorType.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

class Cursor;

class CursorType
{
public:
    CursorType(const CXType &handle);

    std::string GetDisplayName(void) const;

    int GetArgumentCount(void) const;
    CursorType GetArgument(unsigned index) const;

    CursorType GetCanonicalType(void) const;

    Cursor GetDeclaration(void) const;

    CXTypeKind GetKind(void) const;

    bool IsConst(void) const;

private:
    CXType m_handle;
};