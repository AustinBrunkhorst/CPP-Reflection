/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Tokenizer.hpp
** --------------------------------------------------------------------------*/

template<typename TokenEnumType, typename InputType>
Tokenizer<TokenEnumType, InputType>::Tokenizer(void)
    : m_rootState( CreateState( ) )
{
    
}

template<typename TokenEnumType, typename InputType>
Tokenizer<TokenEnumType, InputType>::~Tokenizer(void)
{
    for (auto *state : m_createdStates)
        delete state;
}

template<typename TokenEnumType, typename InputType>
const typename Tokenizer<TokenEnumType, InputType>::StateType::Handle Tokenizer<TokenEnumType, InputType>::GetRootState(void) const
{
    return m_rootState;
}

template<typename TokenEnumType, typename InputType>
typename Tokenizer<TokenEnumType, InputType>::StateType::Handle Tokenizer<TokenEnumType, InputType>::CreateState(TokenEnumType acceptingType)
{
    auto state = new StateType( acceptingType );

    m_createdStates.push_back( state );

    return state;
}

template<typename TokenEnumType, typename InputType>
void Tokenizer<TokenEnumType, InputType>::LoadSymbols(const SymbolTable &symbols)
{
    for (auto &symbol : symbols)
    {
        auto currentState = m_rootState;

        auto &value = symbol.first;
        auto length = value.size( );

        for (size_t i = 0; i < length; ++i)
        {
            auto character = value[ i ];
            typename StateType::Handle nextState;

            auto isLastCharacter = i == length - 1;

            auto search = currentState->m_edges.find( character );

            // doesn't already exist
            if (search == currentState->m_edges.end( ))
            {
                nextState = CreateState( );

                currentState->AddEdge( nextState, character );
            } 
            else
            {
                nextState = search->second;
            }

            if (isLastCharacter)
                nextState->m_acceptingType = symbol.second;

            currentState = nextState;
        }
    }
}


template<typename TokenEnumType, typename InputType>
typename Tokenizer<TokenEnumType, InputType>::ResultType Tokenizer<TokenEnumType, InputType>::Tokenize(const InputType &input) const
{
    typename ResultType::TokenList tokens;

    auto iterator = input.begin( );

    while (iterator < input.end( ))
    {
        TokenType token;

        readToken( iterator, input.end( ), token );

        iterator += token.value.size( );

        if (token.value.empty( ))
            ++iterator;
        else
            tokens.push_back( token );
    }

    return ResultType( tokens );
}

template<typename TokenEnumType, typename InputType>
void Tokenizer<TokenEnumType, InputType>::readToken(InputIterator start, InputIterator end, TokenType &outputToken) const
{
    outputToken.type = TokenEnumType::Invalid;

    auto accepted = start;
    auto lastAccepted = start;

    auto currentState = m_rootState;

    auto iterator = start;

    for (; iterator != end; ++iterator)
    {
        auto transition = currentState->m_edges.find( *iterator );
        auto transitionFound = transition != currentState->m_edges.end( );

        auto nextState = transitionFound ?
            transition->second : currentState->m_defaultEdge;

        // terminating state
        if (!nextState)
        {
            accepted = (lastAccepted == start) ? iterator : lastAccepted;

            break;
        }

        if (nextState->m_acceptingType != TokenEnumType::Invalid)
        {
            outputToken.type = nextState->m_acceptingType;

            lastAccepted = iterator + 1;
        }

        currentState = nextState;
    }

    // we read until the end of input
    if (iterator == end)
        accepted = end;

    outputToken.value = InputType( start, accepted );
}