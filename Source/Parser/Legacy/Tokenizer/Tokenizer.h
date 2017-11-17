/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Tokenizer.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Token.h"
#include "TokenizerState.h"
#include "TokenizerResult.h"

template<typename TokenEnumType, typename InputType = std::string>
class Tokenizer
{
public:
    typedef Token<TokenEnumType, InputType> TokenType;
    typedef TokenizerResult<TokenType> ResultType;
    typedef TokenizerState<TokenEnumType, InputType> StateType;
    typedef typename InputType::const_iterator InputIterator;
    typedef std::unordered_map<InputType, TokenEnumType> SymbolTable;

    Tokenizer(void);
    ~Tokenizer(void);

    const typename StateType::Handle GetRootState(void) const;

    typename StateType::Handle CreateState(TokenEnumType acceptingType = TokenEnumType::Invalid);

    void LoadSymbols(const SymbolTable &table);

    ResultType Tokenize(const InputType &input) const;
    
private:
    void readToken(InputIterator start, InputIterator end, TokenType &outputToken) const;

    std::vector<typename StateType::Handle> m_createdStates;

    typename StateType::Handle m_rootState;
};

#include "Impl/Tokenizer.hpp"