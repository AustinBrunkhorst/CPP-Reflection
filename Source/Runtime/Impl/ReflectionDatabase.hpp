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

        template<typename FunctionType, typename FunctionInvoker>
        void ReflectionDatabase::AddGlobalFunction(
            const std::string &name, 
            FunctionType type, 
            FunctionInvoker invoker, 
            const MetaManager::Initializer &meta
        )
        {
            Function function( name, type, invoker );

            function.m_meta = meta;

            globalFunctions[ name ].emplace( 
                function.GetSignature( ), 
                function 
            );
        }
    }
}
