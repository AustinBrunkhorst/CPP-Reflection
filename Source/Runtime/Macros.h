/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Macros.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#ifdef __REFLECTION_PARSER__

#define Meta(...) __attribute__((annotate(#__VA_ARGS__)))

#define META_OBJECT

#else

#define Meta(...)

// Used in objects to preserve virtual inheritance functionality
#define META_OBJECT                                                                                    \
    public:                                                                                            \
    ursine::meta::Type GetType(void) const override                                                    \
    {                                                                                                  \
        return typeof( decltype( *this ) );                                                            \
    }                                                                                                  \
    ursine::meta::Object *Clone(void) const override                                                   \
    {                                                                                                  \
        typedef                                                                                        \
        std::remove_const<                                                                             \
            std::remove_reference<                                                                     \
                decltype( *this )                                                                      \
            >::type                                                                                    \
        >::type ClassType;                                                                             \
        return new ClassType( *this );                                                                 \
    }                                                                                                  \
    private:                                                                                           \

#endif