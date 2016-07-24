/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaDataManager.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "MetaDataManager.h"
#include "ReflectionParser.h"

#include "Tokenizer/TokenType.h"
#include "Tokenizer/Tokenizer.h"

#include <boost/regex.hpp>

#define TOKENS_WHITESPACE   ' ', '\r', '\n', '\t'
#define TOKENS_NUMBER       '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
#define TOKENS_ALPHANUMERIC 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', \
                            'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', \
                            's', 't', 'u', 'v', 'w', 'x', 'y', 'z',      \
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', \
                            'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', \
                            'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'       \

#define LITERAL_ESCAPE_CHAR '\\'
#define LITERAL_SINGLE_QUOTE '\''
#define LITERAL_DOUBLE_QUOTE '"'

#define TOKEN(name, value) { value, ConstructorTokenType::name },

namespace
{
    typedef Token<ConstructorTokenType, std::string> ConstructorToken;

    const Tokenizer<ConstructorTokenType> &getConstructorTokenizer(void);
}

MetaDataManager::MetaDataManager(const Cursor &cursor)
{
    for (auto &child : cursor.GetChildren( ))
    {
        if (child.GetKind( ) != CXCursor_AnnotateAttr)
            continue;

        for (auto &prop : extractProperties( child ))
            m_properties[ prop.first ] = prop.second;
    }
}

std::string MetaDataManager::GetProperty(const std::string &key) const
{
    auto search = m_properties.find( key );

    // use an empty string by default
    return search == m_properties.end( ) ? "" : search->second;
}

bool MetaDataManager::GetFlag(const std::string &key) const
{
    return m_properties.find( key ) == m_properties.end( ) ? false : true;
}

std::string MetaDataManager::GetNativeString(const std::string &key) const
{
    auto search = m_properties.find( key );

    // wasn't set
    if (search == m_properties.end( ))
        return "";

    static const boost::regex quotedString(
        // opening quote
        "(?:\\s*\")"
        // actual string contents
        "([^\"]*)"
        // closing quote
        "\"",
        boost::regex::icase
    );

    auto &value = search->second;
    
    auto flags = boost::match_default | boost::format_all;

    boost::match_results<std::string::const_iterator> match;

    if (boost::regex_search( 
            value.cbegin( ), 
            value.cend( ), 
            match, 
            quotedString, 
            flags 
        )
    )
    {
        return match[ 1 ].str( );
    }

    // couldn't find one
    return "";
}

void MetaDataManager::CompileTemplateData(
    TemplateData &data, 
    const ReflectionParser *context
) const
{
    TemplateData propertyData { TemplateData::Type::List };

    std::vector<std::string> lines;

    // list of keywords to ignore in the initializer list
    static const std::vector<std::string> reservedKeywords
    {
        native_property::Enable,
        native_property::Disable,
        native_property::Register,
        native_property::WhiteListMethods,
        native_property::DisableNonDynamicCtor,
        native_property::DynamicCtorWrap,
        native_property::EnablePtrType,
        native_property::EnableConstPtrType,
        native_property::EnableArrayType,
        native_property::DisplayName,
        native_property::ExplicitGetter,
        native_property::ExplicitSetter,
        native_property::VeryExplicitGetter,
        native_property::VeryExplicitSetter
    };

    int i = 0;

    auto propertyCount = m_properties.size( ) - 1;

    for (auto &prop : m_properties)
    {
        TemplateData item { TemplateData::Type::Object };

        // skip reserved keywords
        if (std::find( 
                reservedKeywords.begin( ), 
                reservedKeywords.end( ), 
                prop.first 
            ) != reservedKeywords.end( )
        )
        {
            --propertyCount;

            continue;
        }

        item[ "type" ] = prop.first;;
        item[ "arguments" ] = prop.second;

        item[ "isLast" ] = utils::TemplateBool( i == propertyCount );

        propertyData << item;

        ++i;
    }

    data[ "metaProperty" ] = propertyData;
    data[ "metaDataInitializerList" ] = 
        context->LoadTemplatePartial( kPartialMetaInitializerList );
}

std::vector<MetaDataManager::Property> MetaDataManager::extractProperties(
    const Cursor &cursor
) const
{
    std::vector<Property> properties;

    auto &tokenizer = getConstructorTokenizer( );

    auto propertyList = cursor.GetDisplayName( );
    auto result = tokenizer.Tokenize( propertyList );

    result.RemoveAll( ConstructorTokenType::Whitespace );

    auto &tokens = result.GetTokens( );
    int tokenCount = static_cast<int>( tokens.size( ) );

    // case where there is only one identifier, which means there's one property
    // with a default constructor
    if (tokenCount == 1 && tokens[ 0 ].type == ConstructorTokenType::Identifier)
    {
        properties.emplace_back( tokens[ 0 ].value, "" );
    }

    auto lastType = ConstructorTokenType::Invalid;

    int firstOpenParenToken = 0;
    int openParens = 0;

    for (int i = 0; i < tokenCount; ++i)
    {
        auto &token = tokens[ i ];

        switch (token.type)
        {
        case ConstructorTokenType::OpenParentheses:
        {
            if (openParens == 0)
                firstOpenParenToken = i;

            ++openParens;

            break;
        }
        case ConstructorTokenType::CloseParentheses:
        {
            --openParens;

            // we've read a constructor
            if (openParens == 0)
            {
                properties.emplace_back(
                    result.ConsumeAllPrevious( std::max( 0, firstOpenParenToken - 1 ),
                        ConstructorTokenType::Identifier, 
                        ConstructorTokenType::ScopeResolution,
                        ConstructorTokenType::LessThan,
                        ConstructorTokenType::GreaterThan
                    ),
                    result.ConsumeRange( firstOpenParenToken + 1, std::max( 0, i - 1 ) )
                );

                ++i;
            }

            break;
        }
        case ConstructorTokenType::Comma:
        {
            // constructor with no parameters
            if (openParens == 0 && lastType == ConstructorTokenType::Identifier)
            {
                properties.emplace_back(
                    result.ConsumeAllPrevious( i - 1, 
                        ConstructorTokenType::Identifier, 
                        ConstructorTokenType::ScopeResolution,
                        ConstructorTokenType::LessThan,
                        ConstructorTokenType::GreaterThan
                    ),
                    ""
                );
            }

            break;
        }
        default:
            break;
        }

        lastType = token.type;
    }

    // case where a default constructor is the last in the list
    if (tokenCount >= 2 && 
        tokens[ tokenCount - 1 ].type == ConstructorTokenType::Identifier &&
        tokens[ tokenCount - 2 ].type == ConstructorTokenType::Comma)
    {
        properties.emplace_back( tokens.back( ).value, "" );
    }

    return properties;
}

namespace
{
    const Tokenizer<ConstructorTokenType> &getConstructorTokenizer(void)
    {
        static bool initialized = false;
        static Tokenizer<ConstructorTokenType> tokenizer;

        if (initialized)
            return tokenizer;

        auto root = tokenizer.GetRootState( );

        // Whitespace
        {
            auto whitespace = tokenizer.CreateState( ConstructorTokenType::Whitespace );

            whitespace->SetLooping( TOKENS_WHITESPACE );

            root->AddEdge( whitespace, TOKENS_WHITESPACE );
        }

        // Identifier
        {
            auto firstCharacter = tokenizer.CreateState( ConstructorTokenType::Identifier );
            auto anyCharacters = tokenizer.CreateState( ConstructorTokenType::Identifier );

            root->AddEdge( firstCharacter, TOKENS_ALPHANUMERIC, '_' );

            anyCharacters->SetLooping( TOKENS_ALPHANUMERIC, TOKENS_NUMBER, '_' );

            firstCharacter->AddEdge( anyCharacters, TOKENS_ALPHANUMERIC, TOKENS_NUMBER, '_' );
        }

        // Integer Literal
        auto integerLiteral = tokenizer.CreateState( ConstructorTokenType::IntegerLiteral );
        {
            integerLiteral->SetLooping( TOKENS_NUMBER );

            root->AddEdge( integerLiteral, TOKENS_NUMBER );
        }

        // Float Literal
        {
            auto period = tokenizer.CreateState( );
            auto floatNoExponent = tokenizer.CreateState( ConstructorTokenType::FloatLiteral );
            auto exponent = tokenizer.CreateState( );
            auto plusOrMinus = tokenizer.CreateState( );
            auto validOptionalExponent = tokenizer.CreateState( ConstructorTokenType::FloatLiteral );
            auto fCharacter = tokenizer.CreateState( ConstructorTokenType::FloatLiteral );

            integerLiteral->AddEdge( period, '.' );
            period->AddEdge( floatNoExponent, TOKENS_NUMBER );

            floatNoExponent->AddEdge( exponent, 'e', 'E' );
            floatNoExponent->SetLooping( TOKENS_NUMBER );

            exponent->AddEdge( validOptionalExponent, TOKENS_NUMBER );
            exponent->AddEdge( plusOrMinus, '+', '-' );

            plusOrMinus->AddEdge( validOptionalExponent, TOKENS_NUMBER );

            validOptionalExponent->AddEdge( fCharacter, 'f', 'F' );
            validOptionalExponent->SetLooping( TOKENS_NUMBER );

            floatNoExponent->AddEdge( fCharacter, 'f', 'F' );
        }

        // String Literal
        {
            auto firstDoubleQuote = tokenizer.CreateState( );
            auto escapeSlash = tokenizer.CreateState(  );
            auto escapeChars = tokenizer.CreateState( );
            auto validStringLiteral = tokenizer.CreateState( ConstructorTokenType::StringLiteral );
            auto anyCharacter = tokenizer.CreateState( );

            root->AddEdge( firstDoubleQuote, LITERAL_DOUBLE_QUOTE );

            firstDoubleQuote->AddEdge( escapeSlash, LITERAL_ESCAPE_CHAR );
            firstDoubleQuote->AddEdge( validStringLiteral, LITERAL_DOUBLE_QUOTE );
            firstDoubleQuote->SetDefaultEdge( anyCharacter );

            escapeSlash->AddEdge( escapeChars, LITERAL_DOUBLE_QUOTE );

            // accept any escape token
            escapeSlash->SetDefaultEdge( firstDoubleQuote );

            escapeChars->SetDefaultEdge( firstDoubleQuote );
            escapeChars->AddEdge( validStringLiteral, LITERAL_DOUBLE_QUOTE );

            anyCharacter->SetDefaultEdge( anyCharacter );
            anyCharacter->AddEdge( escapeSlash, LITERAL_ESCAPE_CHAR );
            anyCharacter->AddEdge( validStringLiteral, LITERAL_DOUBLE_QUOTE );
        }

        // Symbols
        {
            decltype(tokenizer)::SymbolTable symbols
            {
                #include "Tokenizer/ConstructorTokenSymbols.inl"
            };

            tokenizer.LoadSymbols( symbols );
        }

        return tokenizer;
    }
}