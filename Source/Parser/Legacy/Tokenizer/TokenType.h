/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TokenType.h
** --------------------------------------------------------------------------*/

#pragma once

#define TOKEN(name, value) name,

enum class ConstructorTokenType
{
    Invalid,
    Whitespace,
    Identifier,
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    SYMBOL_START,

    #include "ConstructorTokenSymbols.inl"

    SYMBOL_END
};

#undef TOKEN