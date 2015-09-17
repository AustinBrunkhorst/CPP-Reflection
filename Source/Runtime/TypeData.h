/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** TypeData.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
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
        struct TypeData
        {
            bool isEnum : 1;
            bool isPrimitive : 1;
            bool isPointer : 1;
            bool isClass : 1;

            MetaManager meta;

            std::string name;

            // enum type

            Enum enumeration;

            // class type

            Type::Set baseClasses;
            Type::Set derivedClasses;

            Destructor destructor;

            std::unordered_map<
                InvokableSignature, 
                Constructor
            > constructors;

            std::unordered_map<
                InvokableSignature, 
                Constructor
            > dynamicConstructors;

            std::unordered_map<
                std::string, 
                Field
            > fields;

            std::unordered_map<
                std::string, 
                Global
            > staticFields;

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

            ~TypeData(void);

            void LoadBaseClasses(
                ReflectionDatabase &db, 
                TypeID thisType, 
                const std::initializer_list<Type> &classes
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename ClassType, typename ...Args>
            void AddConstructor(
                Constructor::Invoker invoker, 
                const MetaManager::Initializer &meta, 
                bool isDynamic
            );

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

            template<typename ClassType, typename FieldType>
            void AddField(
                const std::string &name, 
                Field::Getter getter, 
                Field::Setter setter, 
                const MetaManager::Initializer &meta
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename ClassType, typename FieldType>
            void AddStaticField(
                const std::string &name, 
                Global::Getter getter, 
                Global::Setter setter, 
                const MetaManager::Initializer &meta
            );

            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////

            template<typename MethodType, typename MethodInvoker>
            void AddMethod(
                const std::string &name, 
                MethodType type, 
                MethodInvoker invoker, 
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
                typename FunctionType, 
                typename FunctionInvoker
            >
            void AddStaticMethod(
                const std::string &name, 
                FunctionType type, 
                FunctionInvoker invoker, 
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
                const typename EnumContainer<EnumType>::Table &table
            );
        };
    }
}

#include "Impl/TypeData.hpp"