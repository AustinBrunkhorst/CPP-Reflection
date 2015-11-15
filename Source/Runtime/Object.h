/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** Object.h
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        class Type;

        class Object
        {
        public:
            virtual ~Object(void) { }

            virtual Type GetType(void) const = 0;
            virtual Object *Clone(void) const = 0;
        };
    }
}