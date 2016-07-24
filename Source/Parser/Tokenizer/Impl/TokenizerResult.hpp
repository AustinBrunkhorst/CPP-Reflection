/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TokenizerResult.hpp
** --------------------------------------------------------------------------*/

template<typename TokenType>
TokenizerResult<TokenType>::TokenizerResult(const TokenList &tokens)
    : m_tokens( tokens ) { }

template<typename TokenType>
const typename TokenizerResult<TokenType>::TokenList &TokenizerResult<TokenType>::GetTokens(void) const
{
    return m_tokens;
}

template<typename TokenType>
template<typename... TokenTypeList>
size_t TokenizerResult<TokenType>::FindNext(size_t start, TokenTypeList &&...types)
{
    std::vector<typename TokenType::EnumType> toMatch { std::forward<TokenTypeList>( types )... };

    for (auto i = start; i < m_tokens.size( ); ++i)
    {
        auto search = std::find( toMatch.begin( ), toMatch.end( ), m_tokens[ i ].type );

        if (search != toMatch.end( ))
            return i;
    }

    return m_tokens.size( ) - 1;
}

template<typename TokenType>
template<typename... TokenTypeList>
size_t TokenizerResult<TokenType>::FindPrevious(size_t start, TokenTypeList &&...types)
{
    std::vector<typename TokenType::EnumType> toMatch { std::forward<TokenTypeList>( types )... };

    for (auto i = 0; i <= start; ++i)
    {
        auto search = std::find( toMatch.begin( ), toMatch.end( ), m_tokens[ start - i ].type );

        if (search != toMatch.end( ))
            return i;
    }

    return 0;
}

template<typename TokenType>
template<typename... TokenTypeList>
void TokenizerResult<TokenType>::RemoveAll(TokenTypeList &&...types)
{
    std::vector<typename TokenType::EnumType> toRemove { std::forward<TokenTypeList>( types )... };

    auto removed = std::remove_if( 
        m_tokens.begin( ), 
        m_tokens.end( ), 
        [&](const TokenType &token) {
            return std::find( toRemove.begin( ), toRemove.end( ), token.type ) != toRemove.end( );
        }
    );

    m_tokens.erase( removed, m_tokens.end( ) );
}

template<typename TokenType>
typename TokenType::InputValueType TokenizerResult<TokenType>::ConsumeRange(size_t start, size_t end)
{
    typename TokenType::InputValueType consumed { };

    // constrict range
    end = std::min( end, m_tokens.size( ) - 1 );

    for (auto i = start; i <= end; ++i)
        consumed += m_tokens[ i ].value;

    return consumed;
}

template<typename TokenType>
template<typename... TokenTypeList>
typename TokenType::InputValueType TokenizerResult<TokenType>::ConsumeAllPrevious(size_t start, TokenTypeList &&...types)
{
    std::vector<typename TokenType::EnumType> toConsume { std::forward<TokenTypeList>( types )... };

    std::vector<typename TokenType::InputValueType *> consumed;

    for (size_t i = 0; i <= start; ++i)
    {
        auto &token = m_tokens[ start - i ];

        auto search = std::find( toConsume.begin( ), toConsume.end( ), token.type );

        if (search == toConsume.end( ))
            break;

        consumed.emplace_back( &token.value );
    }

    typename TokenType::InputValueType result { };

    for (auto it = consumed.rbegin( ); it != consumed.rend( ); ++it)
        result += *( *it );

    return result;
}

template<typename TokenType>
template<typename... TokenTypeList>
typename TokenType::InputValueType TokenizerResult<TokenType>::ConsumeAllNext(size_t start, TokenTypeList &&...types)
{
    std::vector<typename TokenType::EnumType> toConsume { std::forward<TokenTypeList>( types )... };

    typename TokenType::InputValueType consumed { };

    for (size_t i = start; i < m_tokens.size( ); ++i)
    {
        auto &token = m_tokens[ start - i ];

        auto search = std::find( toConsume.begin( ), toConsume.end( ), token.type );

        if (search == toConsume.end( ))
            break;

        consumed += token.value;
    }

    return consumed;
}