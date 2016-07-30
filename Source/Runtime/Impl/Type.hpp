/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Type.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "TypeUnpacker.hpp"

#include "../Variant.h"
//#include "../Constructor.h"

#include "../Common/Logging.h"

namespace std
{
    template<>
    struct hash<ursine::meta::Type>
    {
        size_t operator()(const ursine::meta::Type &type) const
        {
            return hash<ursine::meta::TypeID>( )( type.GetID( ) );
        }
    };
}

namespace ursine
{
    namespace meta
    {
        template<typename T>
        Type Type::Get(T &&obj)
        {
            return { typeof( T ) };
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename T>
        bool Type::DerivesFrom(void) const
        {
            return DerivesFrom( typeof( T ) );
        }

        template<typename ClassType>
        Json Type::SerializeJson(const ClassType &instance, bool invokeHook)
        {
            auto type = typeof( ClassType );

            UAssert( type.IsValid( ),
                "Invalid type serialized."
            );

            Variant variant = instance;

            return type.SerializeJson( variant, invokeHook );
        }

        template<typename ClassType>
        ClassType Type::DeserializeJson(const Json &value)
        {
            auto type = typeof( ClassType );

            UAssert( type.IsValid( ),
                "Invalid type created."
            );

            return type.DeserializeJson( value ).GetValue<ClassType>( );
        }
    }
}
