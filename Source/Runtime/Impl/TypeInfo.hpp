/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeInfo.hpp
** --------------------------------------------------------------------------*/

#include "Common/Compiler.h"

#if defined(COMPILER_MSVC)

#pragma warning(push)

// unused template parameters
#pragma warning(disable : 4544)

#endif

namespace ursine
{
    namespace meta
    {
        template<typename T>
        TypeID TypeInfo<T>::ID = Type::Invalid;

        template<typename T>
        bool TypeInfo<T>::Defined = false;

        template<typename T>
        void TypeInfo<T>::Register(
            TypeID id, 
            TypeData &data, 
            bool beingDefined
        )
        {
            // already defined
            if (id == Type::Invalid)
                return;

            ID = id;
        
            typedef typename std::remove_pointer< std::decay<T>::type >::type Decayed;

            data.isClass = std::is_class< Decayed >::value;
            data.isEnum = std::is_enum< Decayed >::value;
            data.isPointer = std::is_pointer< T >::value;
            data.isPrimitive = std::is_arithmetic< Decayed >::value;
            data.isFloatingPoint = std::is_floating_point< Decayed >::value;
            data.isSigned = std::is_signed< Decayed >::value;
        
            if (beingDefined)
            {
                addDefaultConstructor( data );

                applyTrivialAttributes( data );
            }
        }

        template<typename T>
        template<typename U = T>
        void TypeInfo<T>::addDefaultConstructor(
            TypeData &data, 
            typename std::enable_if< 
                !std::is_trivially_default_constructible<U>::value 
            >::type*
        )
        {
            // do nothing
        }

        template<typename T>
        template<typename U = T>
        void TypeInfo<T>::addDefaultConstructor(
            TypeData &data, 
            typename std::enable_if< 
                std::is_trivially_default_constructible<U>::value 
            >::type*
        )
        {
            // add the good 'ol default constructor
            data.AddConstructor<T, false, false>( { } );

             // add the good 'ol dynamic default constructor
            data.AddConstructor<T, true, false>( { } );
        }

        template<typename T>
        template<typename U = T>
        void TypeInfo<T>::applyTrivialAttributes(
            TypeData &data, 
            typename std::enable_if< 
                !std::is_trivial<U>::value 
            >::type* = nullptr
        )
        {
            // do nothing
        }

        template<typename T>
        template<typename U = T>
        void TypeInfo<T>::applyTrivialAttributes(
            TypeData &data, 
            typename std::enable_if< 
                std::is_trivial<U>::value 
            >::type* = nullptr
        )
        {
            data.SetDestructor<T>( );
        }
    }
}

#if defined(COMPILER_MSVC)

#pragma warning(pop)

#endif