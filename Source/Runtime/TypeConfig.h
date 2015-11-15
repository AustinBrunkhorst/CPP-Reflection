/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** TypeConfig.h
** --------------------------------------------------------------------------*/

#pragma once

#include <type_traits>

// converts the type name into a meta::Type instance
#define typeof(type)                          \
	ursine::meta::Type( 					  \
		ursine::meta::TypeInfo<               \
			ursine::meta::CleanedType< type > \
		>::ID                                 \
	)                                         \

namespace ursine
{
    namespace meta
    {
        template<typename T>
        using CleanedType = 
        	typename std::remove_cv< 
        		typename std::remove_reference< T >::type 
    		>::type;

        typedef unsigned TypeID;
    }
}