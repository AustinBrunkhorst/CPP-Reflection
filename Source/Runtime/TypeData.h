/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeData.h
** --------------------------------------------------------------------------*/

#pragma once

#include "MetaManager.h"

#include "Constructor.h"
#include "Destructor.h"

#include "Field.h"
#include "Global.h"

#include "Method.h"
#include "Function.h"

#include "Enum.h"
#include "EnumContainer.h"

namespace ursine
{
    namespace meta
    {
        class ReflectionDatabase;

        struct TypeData
        {
            bool isEnum : 1;
            bool isPrimitive : 1;
            bool isSigned : 1;
            bool isFloatingPoint : 1;
            bool isPointer : 1;
            bool isClass : 1;

            MetaManager meta;

            std::string name;

            // enum type

            Enum enumeration;

            // class type

            Type::Set baseClasses;
            Type::Set derivedClasses;

            Constructor arrayConstructor;

            Destructor destructor;

            std::unordered_map<
                InvokableSignature, 
                Constructor
            > constructors;

            std::unordered_map<
                InvokableSignature, 
                Constructor
            > dynamicConstructors;

            std::vector<Field> fields;
            std::vector<Global> staticFields;

            std::unordered_map<
                std::string, 
                InvokableOverloadMap<Method>
            > methods;

            std::unordered_map<
                std::string, 
                InvokableOverloadMap<Function>
            > staticMethods;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            TypeData(void);
            TypeData(const std::string &name);

            void LoadBaseClasses(
                ReflectionDatabase &db, 
                TypeID thisType, 
                const std::initializer_list<Type> &classes
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename ClassType, bool IsDynamic, bool IsWrapped, typename ...Args>
            void AddConstructor(
                const MetaManager::Initializer &meta
            );

            template<typename ClassType>
            void SetArrayConstructor(void);

            const Constructor &GetConstructor(
                const InvokableSignature &signature
            );

            const Constructor &GetDynamicConstructor(
                const InvokableSignature &signature
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename ClassType>
            void SetDestructor(void);

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////
            
            // Method Getter, Method Setter
            template<typename ClassType, typename FieldType, typename GetterReturnType, typename SetterArgumentType>
            void AddField(
                const std::string &name,
                GetterReturnType (ClassType::*methodGetter)(void),
                void (ClassType::*methodSetter)(SetterArgumentType),
                const MetaManager::Initializer &meta
            );

            // Const Method Getter, Method Setter
            template<typename ClassType, typename FieldType, typename GetterReturnType, typename SetterArgumentType>
            void AddField(
                const std::string &name,
                GetterReturnType (ClassType::*methodGetter)(void) const,
                void (ClassType::*methodSetter)(SetterArgumentType),
                const MetaManager::Initializer &meta
            );


            // Method Getter, Field Setter
            template<typename ClassType, typename FieldType, typename GetterReturnType>
            void AddField(
                const std::string &name, 
                GetterReturnType (ClassType::*methodGetter)(void),
                typename FieldSetter<ClassType, FieldType, false>::Signature fieldSetter,
                const MetaManager::Initializer &meta
            );

            // Const Method Getter, Field Setter
            template<typename ClassType, typename FieldType, typename GetterReturnType>
            void AddField(
                const std::string &name, 
                GetterReturnType (ClassType::*methodGetter)(void) const,
                typename FieldSetter<ClassType, FieldType, false>::Signature fieldSetter,
                const MetaManager::Initializer &meta
            );

            // Field Getter, Method Setter
            template<typename ClassType, typename FieldType, typename SetterArgumentType>
            void AddField(
                const std::string &name, 
                typename FieldGetter<ClassType, FieldType, false>::Signature fieldGetter,
                void (ClassType::*methodSetter)(SetterArgumentType),
                const MetaManager::Initializer &meta
            );

            // Field Getter, Field Setter
            template<typename ClassType, typename FieldType>
            void AddField(
                const std::string &name, 
                typename FieldGetter<ClassType, FieldType, false>::Signature fieldGetter,
                typename FieldSetter<ClassType, FieldType, false>::Signature fieldSetter,
                const MetaManager::Initializer &meta
            );

            const Field &GetField(const std::string &name) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            // Method Getter, Method Setter
            template<typename ClassType, typename FieldType, typename GetterType, typename SetterType>
            void AddStaticField(
                const std::string &name, 
                GetterType getter,
                SetterType setter,
                const MetaManager::Initializer &meta
            );

            // Method Getter, Field Setter
            template<typename ClassType, typename FieldType, typename GetterType>
            void AddStaticField(
                const std::string &name, 
                GetterType getter,
                FieldType *fieldSetter,
                const MetaManager::Initializer &meta
            );

            // Field Getter, Method Setter
            template<typename ClassType, typename FieldType, typename SetterType>
            void AddStaticField(
                const std::string &name, 
                FieldType *fieldGetter,
                SetterType setter,
                const MetaManager::Initializer &meta
            );

            // Field Getter, Field Setter
            template<typename ClassType, typename FieldType>
            void AddStaticField(
                const std::string &name, 
                FieldType *fieldGetter,
                FieldType *fieldSetter,
                const MetaManager::Initializer &meta
            );

            const Global &GetStaticField(const std::string &name) const;

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename MethodType>
            void AddMethod(
                const std::string &name, 
                MethodType method,
                const MetaManager::Initializer &meta
            );

            const Method &GetMethod(
                const std::string &name
            );

            const Method &GetMethod(
                const std::string &name, 
                const InvokableSignature &signature
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<
                typename ClassType, 
                typename FunctionType
            >
            void AddStaticMethod(
                const std::string &name, 
                FunctionType function,
                const MetaManager::Initializer &meta
            );

            const Function &GetStaticMethod(
                const std::string &name
            );

            const Function &GetStaticMethod(
                const std::string &name, 
                const InvokableSignature &signature
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename EnumType>
            void SetEnum(
                const std::string &name, 
                const typename EnumContainer<EnumType>::Initializer &initalizer
            );
        };
    }
}

#include "Impl/TypeData.hpp"