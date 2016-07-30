/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionDatabase.h
** --------------------------------------------------------------------------*/

#pragma once

#include "TypeData.h"
#include "TypeInfo.h"

#include <vector>
#include <unordered_map>

namespace ursine
{
    namespace meta
    {
        class ReflectionDatabase
        {
        public:
            ReflectionDatabase(void);
            ~ReflectionDatabase(void);

            std::vector<TypeData> types;

            std::unordered_map<std::string, TypeID> ids;

            std::unordered_map<std::string, Global> globals;
            
            std::unordered_map<
                std::string, 
                InvokableOverloadMap<Function>
            > globalFunctions;

            ////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////

            static ReflectionDatabase &Instance(void);

            ////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////

            TypeID AllocateType(const std::string &name);

            ////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////

            // Function Getter, Function Setter
            template<typename GlobalType, typename GetterType, typename SetterType>
            void AddGlobal(
                const std::string &name,
                GetterType getter,
                SetterType setter,
                const MetaManager::Initializer &meta
            );

            // Function Getter, Raw Setter
            template<typename GlobalType, typename GetterType>
            void AddGlobal(
                const std::string &name,
                GetterType getter,
                GlobalType *globalSetter,
                const MetaManager::Initializer &meta
            );

            // Raw Getter, Function Setter
            template<typename GlobalType, typename SetterType>
            void AddGlobal(
                const std::string &name,
                GlobalType *globalGetter,
                SetterType setter,
                const MetaManager::Initializer &meta
            );

            // Raw Getter, Raw Setter
            template<typename GlobalType>
            void AddGlobal(
                const std::string &name,
                GlobalType *globalGetter,
                GlobalType *globalSetter,
                const MetaManager::Initializer &meta
            );

            ////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////

            template<typename FunctionType>
            void AddGlobalFunction(
                const std::string &name, 
                FunctionType globalFunction,
                const MetaManager::Initializer &meta
            );

            const Function &GetGlobalFunction(const std::string &name);

            const Function &GetGlobalFunction(
                const std::string &name, 
                const InvokableSignature &signature
            );

        private:
            TypeID m_nextID;
        };
    }
}

#include "Impl/ReflectionDatabase.hpp"