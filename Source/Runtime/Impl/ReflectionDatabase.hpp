/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionDatabase.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename GlobalType, typename GetterType, typename SetterType>
        void ReflectionDatabase::AddGlobal(const std::string &name, GetterType getter, SetterType setter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<GlobalType, true> GlobalGetterType;
            typedef GlobalSetter<GlobalType, true> GlobalSetterType;

            Global global {
                name,
                typeof( GlobalType ),
                !getter ? nullptr : new GlobalGetterType(
                    reinterpret_cast<typename GlobalGetterType::Signature>( getter )
                ),
                !setter ? nullptr : new GlobalSetterType(
                    reinterpret_cast<typename GlobalSetterType::Signature>( setter )
                )
            };

            global.m_meta = meta;

            globals.emplace( name, global );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType, typename GetterType>
        void ReflectionDatabase::AddGlobal(const std::string &name, GetterType getter, GlobalType *globalSetter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<GlobalType, true> GlobalGetterType;
            typedef GlobalSetter<GlobalType, false> GlobalSetterType;

            Global global {
                name,
                typeof( GlobalType ),
                !getter ? nullptr : new GlobalGetterType(
                    reinterpret_cast<typename GlobalGetterType::Signature>( getter )
                ),
                !globalSetter ? nullptr : new GlobalSetterType( globalSetter )
            };

            global.m_meta = meta;

            globals.emplace( name, global );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType, typename SetterType>
        void ReflectionDatabase::AddGlobal(const std::string &name, GlobalType *globalGetter, SetterType setter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<GlobalType, false> GlobalGetterType;
            typedef GlobalSetter<GlobalType, true> GlobalSetterType;

            Global global {
                name,
                typeof( GlobalType ),
                !globalGetter ? nullptr : new GlobalGetterType( globalGetter ),
                !setter ? nullptr : new GlobalSetterType(
                    reinterpret_cast<typename GlobalSetterType::Signature>( setter )
                )
            };

            global.m_meta = meta;

            globals.emplace( name, global );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename GlobalType>
        void ReflectionDatabase::AddGlobal(const std::string &name, GlobalType *globalGetter, GlobalType *globalSetter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<GlobalType, false> GlobalGetterType;
            typedef GlobalSetter<GlobalType, false> GlobalSetterType;

            Global global {
                name,
                typeof( GlobalType ),
                !globalGetter ? nullptr : new GlobalGetterType( globalGetter ),
                !globalSetter ? nullptr : new GlobalSetterType( globalSetter )
            };

            global.m_meta = meta;

            globals.emplace( name, global );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename FunctionType>
        void ReflectionDatabase::AddGlobalFunction(
            const std::string &name, 
            FunctionType globalFunction,
            const MetaManager::Initializer &meta
        )
        {
            Function function( name, globalFunction );

            function.m_meta = meta;

            globalFunctions[ name ].emplace( 
                function.GetSignature( ), 
                function 
            );
        }
    }
}
