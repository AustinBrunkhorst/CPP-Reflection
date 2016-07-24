/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** MetaProperty.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Object.h"

#include "Macros.h"

namespace ursine 
{ 
    namespace meta
    {
        class MetaProperty : public Object
        {

        };

        template<typename PropertyType, typename ...Args>
        MetaProperty *MetaPropertyInitializer(Args&&... args);
    } 
}

#pragma region Built-In Parser Properties

#if (!defined(__REFLECTION_PARSER__) && defined(__INTELLISENSE__))

/** @brief Enables introspection of this type.
 *         You can also enable a class type by inheriting from ursine::meta::Object.
 */
class Enable : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Only registers this type. Does not generate class information.
 */
class Register : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Explicitly disables introspection of this type.
 */
class Disable : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Requires all methods in a class to be whitelisted by default.
 */
class WhiteListMethods : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Explicitly disables generation of non dynamic constructors.
 *         Only applies to class constructors.
 */
class DisableNonDynamic : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Uses the "WrapObject" Variant policy in dynamic constructors.
 */
class WrapObject : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Explicitly enables generation of pointers to class types.
 *         Applies to class types.
 */
class EnablePtrType : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Explicitly enables generation of constant pointers to class types.
 *         Applies to class types.
 */
class EnableConstPtrType : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Explicitly enables generation of the array type for this type.
 */
class EnableArrayType : public ursine::meta::MetaProperty { };

///////////////////////////////////////////////////////////////////////////////

/** @brief Defines an explicit getter for this type.
 *         Applies to Globals, Fields and Static Fields.
 */
class Getter : public ursine::meta::MetaProperty
{
public:
    /** @param getterName Name of the getter function. 
     *         The name is relative to the context. 
     *         For example, in a class the name is a public member function.
     *         In a Global or Static Field, it's a globally accessible function.
     */
    Getter(const char *getterName);
};

///////////////////////////////////////////////////////////////////////////////

/** @brief Defines an explicit setter for this type.
 *         Applies to Globals, Fields and Static Fields.
 */
class Setter : public ursine::meta::MetaProperty
{
public:
    /** @param setterName Name of the setter function.
     *         The name is relative to the context.
     *         For example, in a class the name is a public member function.
     *         In a Global or Static Field, it's a globally accessible function.
     */
    Setter(const char *setterName);
};

/** @brief Defines an explicit getter for this type. Parent type is not assumed
 *         Applies to Globals, Fields and Static Fields.
 */
class ExplicitGetter : public ursine::meta::MetaProperty
{
public:
    /** @param getterName Name of the getter function.
     */
    ExplicitGetter(const char *getterName);
};

///////////////////////////////////////////////////////////////////////////////

/** @brief Defines an explicit setter for this type. Parent type is not assumed
 *         Applies to Globals, Fields and Static Fields.
 */
class ExplicitSetter : public ursine::meta::MetaProperty
{
public:
    /** @param setterName Name of the setter function.
     */
    ExplicitSetter(const char *setterName);
};

///////////////////////////////////////////////////////////////////////////////

/** @brief Overrides the display name of a type. Only affects GetX( ) Type functions.
 *         Applies to Enums, Classes, Fields, Functions, Globals and Methods
 */
class DisplayName : public ursine::meta::MetaProperty
{
public:
    /** @param displayName Name of the setter function.
     *         The name is relative to the context.
     *         For example, in a class the name is a public member function.
     *         In a Global or Static Field, it's a globally accessible function.
     */
    DisplayName(const char *displayName);
};

#endif // if (!defined(__REFLECTION_PARSER__) && defined(__INTELLISENSE__))

#pragma endregion

#include "Impl/MetaProperty.hpp"