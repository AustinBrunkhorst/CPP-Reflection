/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** EnumContainer.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename EnumType>
        EnumContainer<EnumType>::EnumContainer(
            const std::string &name, 
            const Initializer &initializer
        )
            : EnumBase( name, InvalidTypeID )
        {
            for (auto &pair : initializer)
            {
                m_keys.emplace_back( pair.first );

                m_keyToValue.emplace( pair );
            }
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        EnumContainer<EnumType>::EnumContainer(
            const std::string &name, 
            const Initializer &initializer,
            TypeID owner
        )
            : EnumBase( name, owner )
        {
            for (auto &pair : initializer)
            {
                m_keys.emplace_back( pair.first );

                m_keyToValue.emplace( pair );
            }
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        Type EnumContainer<EnumType>::GetType(void) const
        {
            return typeof( EnumType );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        Type EnumContainer<EnumType>::GetUnderlyingType(void) const
        {
            return typeof( typename std::underlying_type<EnumType>::type );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        const std::vector<std::string> &EnumContainer<EnumType>::GetKeys(void) const
        {
            return m_keys;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        std::vector<Variant> EnumContainer<EnumType>::GetValues(void) const
        {
            std::vector<Variant> values;

            for (auto &entry : m_keyToValue)
                values.emplace_back( entry.second );

            return values;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        std::string EnumContainer<EnumType>::GetKey(const Argument &value) const
        {
            typedef 
            typename std::underlying_type< EnumType >::type UnderlyingType;

            auto type = value.GetType( );

            // invalid type
            if (type != typeof( EnumType ) &&
                type != typeof( UnderlyingType ))
            {
                return std::string( );
            }

            auto &converted = value.GetValue<EnumType>( );

            for (auto &entry : m_keyToValue)
            {
                if (entry.second == converted)
                    return entry.first;
            }

            return std::string( );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        Variant EnumContainer<EnumType>::GetValue(const std::string &key) const
        {
            auto search = m_keyToValue.find( key );

            // not found
            if (search == m_keyToValue.end( ))
                return Variant( );

            return Variant( search->second );
        }
    }
}
