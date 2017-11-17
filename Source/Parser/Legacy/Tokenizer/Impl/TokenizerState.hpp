/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TokenizerState.hpp
** --------------------------------------------------------------------------*/

template<typename TokenEnumType, typename InputType>
TokenizerState<TokenEnumType, InputType>::TokenizerState(TokenEnumType acceptingType)
    : m_acceptingType( acceptingType )
    , m_defaultEdge( nullptr ) { }

template<typename TokenEnumType, typename InputType>
void TokenizerState<TokenEnumType, InputType>::SetAcceptingType(TokenEnumType acceptingType)
{
    m_acceptingType = acceptingType;
}

template<typename TokenEnumType, typename InputType>
void TokenizerState<TokenEnumType, InputType>::AddEdge(Handle to, char character)
{
    m_edges[ character ] = to;
}

template<typename TokenEnumType, typename InputType>
template<typename ... CharacterList>
void TokenizerState<TokenEnumType, InputType>::AddEdge(Handle to, char character, CharacterList &&...list)
{
    AddEdge( to, character );
    AddEdge( to, list... );
}

template<typename TokenEnumType, typename InputType>
template<typename ... CharacterList>
void TokenizerState<TokenEnumType, InputType>::SetLooping(CharacterList &&...list)
{
    AddEdge( Handle( this ), list... );
}

template<typename TokenEnumType, typename InputType>
void TokenizerState<TokenEnumType, InputType>::SetDefaultEdge(Handle defaultEdge)
{
    m_defaultEdge = defaultEdge;
}