#include "VariantContainer.h"
#include "ObjectWrapper.h"

namespace ursine
{
    namespace meta
    {
        template <typename T>
        Variant::Variant(
            T *data, 
            variant_policy::WrapObject, 
            typename std::enable_if< 
                std::is_base_of<Object, T>::value 
            >::type*
        )
            : m_isConst( std::is_const<T>::value )
            , m_base( 
                new ObjectWrapper( 
                    static_cast<Object *>( 
                        const_cast< typename std::remove_const<T>::type*>(
                            data 
                        )
                    ) 
                ) 
            )
        {

        }

        template<typename T>
        Variant::Variant(T &data)
            : m_isConst( std::is_pointer<T>::value && std::is_const<T>::value )
            , m_base( new VariantContainer< CleanedType<T> >( data ) )
        {
        
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant::Variant(T &&data, 
            typename std::enable_if< 
                !std::is_same<Variant&, T>::value 
            >::type*, 
            typename std::enable_if< 
                !std::is_const<T>::value 
            >::type*
        )
            : m_isConst( false )
            , m_base( 
                new VariantContainer< CleanedType<T> >( 
                    static_cast<T&&>( data ) 
                )
            )
        {

        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        Variant &Variant::operator=(T &&rhs)
        {
            Variant( static_cast<T&&>( rhs ) ).Swap( *this );

            return *this;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        T &Variant::GetValue(void) const
        {
            return *static_cast<T*>( m_base->GetPtr( ) );
        }
    }
}
