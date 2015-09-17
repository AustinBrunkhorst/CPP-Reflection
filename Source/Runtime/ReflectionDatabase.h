/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** ReflectionDatabase.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include "TypeData.h"
#include "TypeInfo.h"

#include <vector>
#include <unordered_map>
#include <functional>

namespace ursine
{
    namespace meta
    {
        class ReflectionDatabase
        {
        public:
            struct Initializer
            {
                Initializer(std::function<void(void)> initializer);
            };

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

            template<typename FunctionType, typename FunctionInvoker>
            void AddGlobalFunction(
                const std::string &name, 
                FunctionType type, 
                FunctionInvoker invoker, 
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