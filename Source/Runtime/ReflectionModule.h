/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionModule.h
** --------------------------------------------------------------------------*/

#pragma once

#include "ReflectionDatabase.h"

#define DECLARE_REFLECTION_MODULE(module)                            \
    namespace meta_generated                                         \
    {                                                                \
        class Module##module : public ursine::meta::ReflectionModule \
        {                                                            \
        public:                                                      \
             Module##module(ursine::meta::ReflectionDatabase &db);   \
            ~Module##module(void);                                   \
        };                                                           \
    }                                                                \

#define UsingModule(module) meta_generated::Module##module _##module( db );

namespace ursine
{
    namespace meta
    {
        class ReflectionModule
        {
        public:
            ReflectionModule(ReflectionDatabase &db);

        protected:
            ReflectionDatabase &db;
        };
    }
}