/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionModule.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "ReflectionModule.h"

namespace ursine
{
    namespace meta
    {
        ReflectionModule::ReflectionModule(ReflectionDatabase &db)
            : db( db ) { }
    }
}