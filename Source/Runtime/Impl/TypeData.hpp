namespace ursine
{
    namespace meta
    {
        template<typename ClassType, typename ... Args>
        void TypeData::AddConstructor(
            Constructor::Invoker invoker, 
            const MetaManager::Initializer &meta, 
            bool isDynamic
        )
        {
            InvokableSignature signature = 
                Invokable::CreateSignature<Args...>( );

            Constructor ctor {
                typeof( ClassType ),
                signature,
                invoker,
                isDynamic
            };

            ctor.m_meta = meta;

            if (isDynamic)
                dynamicConstructors.emplace( signature, ctor );
            else
                constructors.emplace( signature, ctor );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType>
        void TypeData::SetDestructor(void)
        {
            destructor = { 
                typeof( ClassType ), 
                [](Variant &instance)
                {
                    instance.GetValue<ClassType>( ).~ClassType( );
                }
            };
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType>
        void TypeData::AddField(
            const std::string &name, 
            Field::Getter getter, 
            Field::Setter setter, 
            const MetaManager::Initializer &meta
        )
        {
            Field field {
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                getter,
                setter
            };

            field.m_meta = meta;

            fields.emplace( name, field );
        }

        template<typename ClassType, typename FieldType>
        void TypeData::AddStaticField(
            const std::string &name, 
            Global::Getter getter, 
            Global::Setter setter, 
            const MetaManager::Initializer &meta
        )
        {
            Global global {
                name,
                typeof( FieldType ),
                getter,
                setter,
                typeof( ClassType ),
            };

            global.m_meta = meta;

            staticFields.emplace( name, global );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename MethodType, typename MethodInvoker>
        void TypeData::AddMethod(
            const std::string &name, 
            MethodType type, 
            MethodInvoker invoker, 
            const MetaManager::Initializer &meta
        )
        {
            Method method( name, type, invoker );

            method.m_meta = meta;

            methods[ name ].emplace( method.GetSignature( ), method );
        }

        template<typename ClassType, typename FunctionType, typename FunctionInvoker>
        void TypeData::AddStaticMethod(
            const std::string &name, 
            FunctionType type, 
            FunctionInvoker invoker, 
            const MetaManager::Initializer &meta
        )
        {
            Function function( name, type, invoker, typeof( ClassType ) );

            function.m_meta = meta;

            staticMethods[ name ].emplace( function.GetSignature( ), function );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        void TypeData::SetEnum(
            const std::string &name, 
            const typename EnumContainer<EnumType>::Table &table
        )
        {
            enumeration = new EnumContainer<EnumType>( name, table );
        }
    }
}