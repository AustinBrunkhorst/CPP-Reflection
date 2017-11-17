/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Token.h
** --------------------------------------------------------------------------*/

#pragma once

template<typename TokenEnumType, typename InputType>
struct Token
{
    typedef TokenEnumType EnumType;
    typedef InputType InputValueType;

    TokenEnumType type;
    InputType value;

    Token(void);
    Token(TokenEnumType type, const InputType &value);
};

#include "Impl/Token.hpp"