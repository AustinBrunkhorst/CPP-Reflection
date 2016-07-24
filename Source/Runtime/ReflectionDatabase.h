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

            template<typename GlobalType>
            void AddGlobal(
                const std::string &name, 
                Global::Getter getter, 
                Global::Setter setter, 
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