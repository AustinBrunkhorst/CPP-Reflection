namespace ursine
{
    namespace meta
    {
        template<typename PropertyType, typename ...Args>
        MetaProperty *MetaPropertyInitializer(Args&&... args)
        {
            static_assert( std::is_base_of<MetaProperty, PropertyType>::value, 
                "Meta properties must inherit from MetaProperty" );

            return new PropertyType( std::forward<Args>( args )... );
        }
    }
}