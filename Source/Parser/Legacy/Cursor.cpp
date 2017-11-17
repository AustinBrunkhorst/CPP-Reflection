/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Cursor.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "Cursor.h"

#include "MetaUtils.h"

Cursor::Cursor(const CXCursor &handle)
    : m_handle( handle ) { }

CXCursorKind Cursor::GetKind(void) const
{
    return m_handle.kind;
}

Cursor Cursor::GetLexicalParent(void) const
{
    return clang_getCursorLexicalParent( m_handle );
}

Cursor Cursor::GetTemplateSpecialization(void) const
{
    return clang_getSpecializedCursorTemplate( m_handle );
}

std::string Cursor::GetSpelling(void) const
{
    std::string spelling;

    utils::ToString( clang_getCursorSpelling( m_handle ), spelling );

    return spelling;
}

std::string Cursor::GetDisplayName(void) const
{
    std::string displayName;

    utils::ToString( clang_getCursorDisplayName( m_handle ), displayName );

    return displayName;
}

std::string Cursor::GetMangledName(void) const
{
    std::string mangled;

    utils::ToString( clang_Cursor_getMangling( m_handle ), mangled );

    return mangled;
}

std::string Cursor::GetUSR(void) const
{
    std::string usr;

    utils::ToString( clang_getCursorUSR( m_handle ), usr );

    return usr;
}

std::string Cursor::GetSourceFile(void) const
{
    auto range = clang_Cursor_getSpellingNameRange( m_handle, 0, 0 );

    auto start = clang_getRangeStart( range );

    CXFile file;
    unsigned line, column, offset;

    clang_getFileLocation( start, &file, &line, &column, &offset );

    std::string filename;

    utils::ToString( clang_getFileName( file ), filename );

    return filename;
}

bool Cursor::IsDefinition(void) const
{
    return clang_isCursorDefinition( m_handle ) ? true : false;
}

bool Cursor::IsConst(void) const
{
    return clang_CXXMethod_isConst( m_handle ) ? true : false;
}

bool Cursor::IsStatic(void) const
{
    return clang_CXXMethod_isStatic( m_handle ) ? true : false;
}

CX_CXXAccessSpecifier Cursor::GetAccessModifier(void) const
{
    return clang_getCXXAccessSpecifier( m_handle );
}

CX_StorageClass Cursor::GetStorageClass(void) const
{
    return clang_Cursor_getStorageClass( m_handle );
}

CursorType Cursor::GetType(void) const
{
    return clang_getCursorType( m_handle );
}

CursorType Cursor::GetReturnType(void) const
{
    return clang_getCursorResultType( m_handle );
}

CursorType Cursor::GetTypedefType(void) const
{
    return clang_getTypedefDeclUnderlyingType( m_handle );
}

Cursor::List Cursor::GetChildren(void) const
{
    List children;

    auto visitor = [](CXCursor cursor, CXCursor parent, CXClientData data)
    {
        auto container = static_cast<List *>( data );

        container->emplace_back( cursor );

        if (cursor.kind == CXCursor_LastPreprocessing)
            return CXChildVisit_Break;

        return CXChildVisit_Continue;
    };

    clang_visitChildren( m_handle, visitor, &children );

    return children;
}

void Cursor::VisitChildren(Visitor visitor, void *data)
{
    clang_visitChildren( m_handle, visitor, data );
}

unsigned Cursor::GetHash(void) const
{
    return clang_hashCursor( m_handle );
}