/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Invokable.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "LanguageTypes/Invokable.h"

Invokable::Invokable(const Cursor &cursor)
    : m_returnType( utils::GetQualifiedName( cursor.GetReturnType( ) ))
{
    auto type = cursor.GetType( );
    unsigned count = type.GetArgumentCount( );

    m_signature.clear( );

    for (unsigned i = 0; i < count; ++i)
    {
        auto argument = type.GetArgument( i );

        m_signature.emplace_back(
            utils::GetQualifiedName( argument )
        );
    }
}