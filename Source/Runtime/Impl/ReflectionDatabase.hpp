/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ReflectionDatabase.hpp
** --------------------------------------------------------------------------*/

namespace ursine
{
    namespace meta
    {
        template<typename GlobalType>
        void ReflectionDatabase::AddGlobal(
            const std::string &name, 
            Global::Getter getter, 
            Global::Setter setter, 
            const MetaManager::Initializer &meta
        )
        {
            Global global {
                name,
                typeof( GlobalType ),
                getter,
                setter
            };

            global.m_meta = meta;

            globals.emplace( name, global );
        }

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
