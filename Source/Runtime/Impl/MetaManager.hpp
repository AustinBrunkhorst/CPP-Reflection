#include "TypeConfig.h"

namespace ursine
{
    namespace meta
    {
        template<typename PropertyType>
        const PropertyType *MetaManager::GetProperty(void) const
        {
            static_assert( std::is_base_of<MetaProperty, PropertyType>::value, 
                "Type must be a MetaProperty." );
            
            auto type = typeof( PropertyType );

            auto search = m_properties.find( type );

            // doesn't exist
            if (search == m_properties.end( ))
                return nullptr;

            return static_cast<const PropertyType*>( search->second );
        }
    }
}