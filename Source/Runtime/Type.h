/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Type.h
** --------------------------------------------------------------------------*/

#pragma once

#include "Macros.h"

#include "TypeID.h"
#include "TypeConfig.h"
#include "InvokableConfig.h"
#include "ArgumentConfig.h"
#include "JsonConfig.h"

#include <string>
#include <vector>
#include <set>
#include <functional>

namespace ursine
{
    namespace meta
    {
        class Variant;
        class Enum;
        class Constructor;
        class Destructor;
        class Field;
        class Global;
        class Method;
        class Function;
        class Argument;

        class MetaManager;

        class Type
        {
        public:
            typedef std::vector<Type> List;
            typedef std::set<Type> Set;
            typedef std::function<Variant(const Variant &, const Field &)> SerializationGetterOverride;

            Type(void);
            Type(const Type &rhs);
            Type(TypeID id, bool isArray = false);

            operator bool(void) const;

            Type &operator=(const Type &rhs);

            bool operator<(const Type &rhs) const;
            bool operator>(const Type &rhs) const;
            bool operator<=(const Type &rhs) const;
            bool operator>=(const Type &rhs) const;
            bool operator==(const Type &rhs) const;
            bool operator!=(const Type &rhs) const;

            /** @brief Gets an instance of an invalid type.
             */
            static const Type &Invalid(void);

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets the internal id of the type.
             */
            TypeID GetID(void) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all types registered in the main 
             *         reflection database.
             */
            static List GetTypes(void);

            /** @brief Gets a type based on the qualified string name.
             *  @param name Name of the type.
             */
            static Type GetFromName(const std::string &name);

            /** @brief Gets a type by deducing the type of an object.
             *  @param obj Object to deduce type from.
             */
            template<typename T>
            static Type Get(T &&obj);

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all registered global variables.
             */
            static std::vector<Global> GetGlobals(void);

            /** @brief Gets a global variable with the specified name.
             *  @param name Qualified global name.
             */
            static const Global &GetGlobal(const std::string &name);

            /** @brief Gets all registered global functions.
             */
            static std::vector<Function> GetGlobalFunctions(void);

            /** @brief Gets a global function with the specified name, and 
             *         first available overload.
             *  @param name Qualified global function name.
             */
            static const Function &GetGlobalFunction(const std::string &name);

            /** @brief Gets a global function with the specified name, and 
             *         overload signature.
             *  @param name Qualified global function name.
             *  @param signature Signature of the global function.
             */
            static const Function &GetGlobalFunction(
                  const std::string &name, 
                  const InvokableSignature &signature
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Compares two type lists.
             *  @param a First list
             *  @param b Second list
             *  @return true if "a" is identical to "b"
             */
            static bool ListsEqual(const List &a, const List &b);

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Determines if this type is valid.
             *  @return true if the internal id is not Type::INVALID
             */
            bool IsValid(void) const;

            /** @brief Determines if this type is primitive.
             *  @return true if the type is among (int, bool, char, etc).
             */
            bool IsPrimitive(void) const;

            /** @brief Determines if this type is a floating point
             *          float, double, long double, etc.
             *  @return true if the type is among (float, double, long double, etc).
             */
            bool IsFloatingPoint(void) const;

            /** @brief Determines if this type is signed (unsigned int, etc).
             *  @return true if the type is signed.
             */
            bool IsSigned(void) const;

            /** @brief Determines if this type is an enumeration.
             *  @return true if the type is either an enum or enum class.
             */
            bool IsEnum(void) const;

            /** @brief Determines if this type is a pointer.
             *  @return true if the type has any level of indirection. 
             *          ie - (int *), (int **), etc.
             */
            bool IsPointer(void) const;

            /** @brief Determines if this type is a class.
             *  @return true if the type is a class or struct.
             */
            bool IsClass(void) const;

            /** @brief Determines if this type is an array type.
             *  @return true if the type is an array type.
             */
            bool IsArray(void) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets the human readable name for this type.
             *  @return Qualified name of the type as it is declared.
             *          ie - "boost::regex"
             */
            std::string GetName(void) const;

            /** @brief Gets meta data for this type.
             *  @return Meta Data Manager for this type.
             */
            const MetaManager &GetMeta(void) const;

            /** @brief Deconstructs the given object instance.
             *  @param instance Variant object instance to destruct.
             */
            void Destroy(Variant &instance) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets the decayed version of this type.
             *  @return Type with no qualifiers like const, and no pointer.
             *          ie - const int * -> int
             */
            Type GetDecayedType(void) const;

            /** @brief Gets the type that this array type holds.
            *  @return Type this array type holds.
            *          ie - Array<double> -> double
            *          Non array types return itself.
            */
            Type GetArrayType(void) const;

            /** @brief Gets the enumeration representing this type, 
             *         assuming it's an enum type.
             *  @return Reference to the enum type in the reflection database.
             */
            const Enum &GetEnum(void) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Determines if this type derives from the specified 
             *         runtime type.
             *  @param other Other class type.
             *  @return true if both types are class types and this type
             *          derives from "other".
             */
            bool DerivesFrom(const Type &other) const;

            /** @brief Determines if this type derives from the specified 
             *         runtime type.
             *  @return true if both types are class types and this type
             *          derives from "other".
             */
            template<typename T>
            bool DerivesFrom(void) const;

            /** @brief Gets all base classes for this type.
             *  @return Type set of all base classes for this type.
             */
            const Set &GetBaseClasses(void) const;

            /** @brief Gets all classes that derive from this class type.
             *  @return Type set of all derived classes for this type.
             */
            const Set &GetDerivedClasses(void) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all constructors for this type 
             *         assuming it's a class type.
             *  @return Set of constructors for this type.
             */
            std::vector<Constructor> GetConstructors(void) const;

            /** @brief Gets all dynamic constructors for this type 
             *         assuming it's a class type.
             *  @return Set of all dynamic constructors for this type.
             */
            std::vector<Constructor> GetDynamicConstructors(void) const;

            /** @brief Gets a constructor for this type.
             *  @param signature Signature of the constructor.
             *  @return Reference to the constructor with the given signature
             *          in the reflection database.
             */
            const Constructor &GetConstructor(
                  const InvokableSignature &signature = InvokableSignature( )
            ) const;

            /** @brief Gets a dynamic constructor for this type with the 
             *         specified argument signature.
             *  @param signature Signature of the dynamic constructor.
             *  @return Reference to the dynamic constructor with the given 
             *          signature in the reflection database.
             */
            const Constructor &GetDynamicConstructor(
                  const InvokableSignature &signature = InvokableSignature( )
            ) const;

            /** @brief Gets the constructor for this array type.
             *  @return Reference to the array constructor in the reflection database.
             */
            const Constructor &GetArrayConstructor(void) const;

            /** @brief Gets the destructor for this type assuming it's a 
             *         class type.
             *  @return Reference to the destructor in the reflection database.
             */
            const Destructor &GetDestructor(void) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all methods for this type 
             *         assuming it's a class type.
             *  @return Set of methods for this type.
             */
            std::vector<Method> GetMethods(void) const;

            /** @brief Gets a method for this type.
             *  @param name Name of the method.
             *  @return Reference to the method in the reflection database.
             *     If the method doesn't exist, an invalid method.
             *     If the method exists, but has overloads, the first declared.
             */
            const Method &GetMethod(const std::string &name) const;

            /** @brief Gets a method for this type.
             *  @param name Name of the method.
             *  @param signature Specific overload for this method.
             *  @return Reference to the method in the reflection database
             *          with the specified overload. If the specific overload
             *          doesn't exist, an invalid method is returned.
             */
            const Method &GetMethod(
                  const std::string &name, 
                  const InvokableSignature &signature
            ) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all static methods for this type
             *         assuming it's a class type.
             *  @return Set of static methods for this type.
             */
            std::vector<Function> GetStaticMethods(void) const;

            /** @brief Gets a static method for this type.
             *  @param name Name of the static method.
             *  @return Reference to the method in the reflection database.
             *     If the method doesn't exist, an invalid function.
             *     If the method exists, but has overloads, the first declared.
             */
            const Function &GetStaticMethod(const std::string &name) const;

            /** @brief Gets a static method for this type.
             *  @param name Name of the static method.
             *  @param signature Specific overload for this method.
             *  @return Reference to the method in the reflection database
             *          with the specified overload. If the specific overload
             *          doesn't exist, an invalid function is returned.
             */
            const Function &GetStaticMethod(
                  const std::string &name, 
                  const InvokableSignature &signature
            ) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all fields for this type 
             *         assuming it's a class type.
             *  @return Set of fields for this type.
             */
            const std::vector<Field> &GetFields(void) const;

            /** @brief Gets a specific field for this type.
             *  @param name Name of the field.
             *  @return Reference to the field in the reflection database.
             *          If the field doesn't exist, an invalid field.
             */
            const Field &GetField(const std::string &name) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            /** @brief Gets all static fields for this type 
             *         assuming it's a class type.
             *  @return Set of static fields for this type.
             */
            std::vector<Global> GetStaticFields(void) const;

            /** @brief Gets a specific static field for this type.
             *  @param name Name of the static field.
             *  @return Reference to the field in the reflection database.
             *          If the field doesn't exist, an invalid global.
             */
            const Global &GetStaticField(const std::string &name) const;

            template<typename ClassType>
            static Json SerializeJson(const ClassType &instance, bool invokeHook = true);

            Json SerializeJson(const Variant &instance, bool invokeHook = true) const;
            Json SerializeJson(const Variant &instance, SerializationGetterOverride getterOverride, bool invokeHook = true) const;

            template<typename ClassType>
            static ClassType DeserializeJson(const Json &value);

            Variant DeserializeJson(const Json &value) const;
            Variant DeserializeJson(const Json &value, const Constructor &ctor) const;
            void DeserializeJson(Variant &instance, const Json &value) const;

        private:
            friend class std::allocator<Type>;

            friend struct TypeData;

            friend class Variant;
            friend class Argument;
            friend class Enum;
            friend class EnumBase;
            friend class Constructor;
            friend class Destructor;
            friend class Method;
            friend class Field;
            friend class Function;
            friend class Global;

            TypeID m_id;
            bool m_isArray;
        };
    }
}

#include "Impl/Type.hpp"