#include "Precompiled.h"

#include "MetaDataManager.h"
#include "ReflectionParser.h"

#include <boost/regex.hpp>

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
        kMetaEnable,
        kMetaDisable,
        kMetaDisablePtrType,
        kMetaDisableConstPtrType,
        kMetaDisplayName,
        kMetaExplicitGetter,
        kMetaExplicitSetter
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

    static const boost::regex propertyList(
        // property name
        "([a-z\\:]+)"
        // optional whitespace before
        "(?:\\s*)"
        // constructor
        "("
            // opening paren
            "\\("
                // arguments
                "([^\\)]*)"
            // closing paren
            "\\)"
        // end constructor
        ")?"
        // optional comma/whitespace
        "(?:(\\s|,)*)",
        boost::regex::icase
    );

    auto flags = boost::match_default | boost::format_all;

    boost::match_results<std::string::const_iterator> match;

    auto meta = cursor.GetDisplayName( );

    auto start = meta.cbegin( );

    // collect properties and optional arguments
    while (boost::regex_search( 
            start, 
            meta.cend( ), 
            match, 
            propertyList, 
            flags 
        )
    )
    {
        auto name = match[ 1 ].str( );
        auto arguments = match[ 3 ].str( );

        properties.emplace_back( name, arguments );

        // advance the first capture group
        start += match[ 0 ].length( );
    }

    return properties;
}