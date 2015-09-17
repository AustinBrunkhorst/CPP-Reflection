namespace ursine
{
    namespace meta
    {
        template<typename EnumType>
        EnumContainer<EnumType>::EnumContainer(
            const std::string &name, 
            const Table &table
        )
            : EnumBase( name, Type::Invalid )
            , m_table( table ) { }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        EnumContainer<EnumType>::EnumContainer(
            const std::string &name, 
            const Table &table, 
            TypeID owner
        )
            : EnumBase( name, owner )
            , m_table( table ) { }

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
            return typeof( typename std::underlying_type< EnumType >::type );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        std::vector<std::string> EnumContainer<EnumType>::GetKeys(void) const
        {
            std::vector<std::string> keys;

            for (auto &entry : m_table)
                keys.emplace_back( entry.first );

            return keys;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        std::vector<Variant> EnumContainer<EnumType>::GetValues(void) const
        {
            std::vector<Variant> values;

            for (auto &entry : m_table)
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

            for (auto &entry : m_table)
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
            auto search = m_table.find( key );

            // not found
            if (search == m_table.end( ))
                return Variant( );

            return Variant( search->second );
        }
    }
}
