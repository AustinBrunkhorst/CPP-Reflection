/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** TypeData.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "../ReflectionDatabase.h"

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, bool IsDynamic, bool IsWrapped, typename ...Args>
        void TypeData::AddConstructor(
            const MetaManager::Initializer &meta
        )
        {
            InvokableSignature signature =
                Invokable::CreateSignature<Args...>( );

            Constructor ctor {
                typeof( ClassType ),
                signature,
                new ConstructorInvoker<ClassType, IsDynamic, IsWrapped, Args...>( ),
                IsDynamic
            };

            ctor.m_meta = meta;

            if (IsDynamic)
                dynamicConstructors.emplace( signature, ctor );
            else
                constructors.emplace( signature, ctor );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType>
        void TypeData::SetArrayConstructor(void)
        {
            arrayConstructor = Constructor {
                typeof( ClassType ),
                { },
                new ConstructorInvoker<Array<ClassType>, false, false>( ),
                false
            };
        }

        template<typename ClassType, typename FieldType, typename GetterReturnType, typename SetterArgumentType>
        void TypeData::AddField(
            const std::string &name, 
            GetterReturnType (ClassType::*methodGetter)(void), 
            void (ClassType::*methodSetter)(SetterArgumentType), 
            const MetaManager::Initializer &meta
        )
        {
            typedef FieldGetter<ClassType, GetterReturnType, true> GetterType;
            typedef FieldSetter<ClassType, SetterArgumentType, true> SetterType;

            static_assert( std::is_same<typename std::decay<GetterReturnType>::type, typename std::decay<FieldType>::type>::value,
                "Return type of getter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            static_assert( std::is_same<typename std::decay<SetterArgumentType>::type, typename std::decay<FieldType>::type>::value,
                "Argument type of setter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            fields.emplace_back(
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                !methodGetter ? nullptr : new GetterType( methodGetter ),
                !methodSetter ? nullptr : new SetterType( methodSetter )
            );

            fields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType, typename GetterReturnType, typename SetterArgumentType>
        void TypeData::AddField(
            const std::string &name,
            GetterReturnType (ClassType::*methodGetter)(void) const,
            void (ClassType::*methodSetter)(SetterArgumentType),
            const MetaManager::Initializer &meta
        )
        {
            typedef FieldGetter<ClassType, GetterReturnType, true> GetterType;
            typedef FieldSetter<ClassType, SetterArgumentType, true> SetterType;

            static_assert( std::is_same<typename std::decay<GetterReturnType>::type, typename std::decay<FieldType>::type>::value,
                "Return type of getter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            static_assert( std::is_same<typename std::decay<SetterArgumentType>::type, typename std::decay<FieldType>::type>::value,
                "Argument type of setter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            fields.emplace_back(
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                !methodGetter ? nullptr : new GetterType( methodGetter ),
                !methodSetter ? nullptr : new SetterType( methodSetter )    
            );

            fields.back( ).m_meta = meta;
        }

        template<typename ClassType, typename FieldType, typename GetterReturnType>
        void TypeData::AddField(
            const std::string &name, 
            GetterReturnType (ClassType::*methodGetter)(void), 
            typename FieldSetter<ClassType, FieldType, false>::Signature fieldSetter, 
            const MetaManager::Initializer &meta
        )
        {
            typedef FieldGetter<ClassType, GetterReturnType, true> GetterType;

            static_assert( std::is_same<typename std::decay<GetterReturnType>::type, typename std::decay<FieldType>::type>::value,
                "Return type of getter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            fields.emplace_back(
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                !methodGetter ? nullptr : new GetterType( methodGetter ),
                !fieldSetter ? nullptr : new FieldSetter<ClassType, FieldType, false>( fieldSetter )   
            );

            fields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType, typename GetterReturnType>
        void TypeData::AddField(
            const std::string &name,
            GetterReturnType (ClassType::*methodGetter)(void) const,
            typename FieldSetter<ClassType, FieldType, false>::Signature fieldSetter,
            const MetaManager::Initializer &meta
        )
        {
            typedef FieldGetter<ClassType, GetterReturnType, true> GetterType;

            static_assert( std::is_same<typename std::decay<GetterReturnType>::type, typename std::decay<FieldType>::type>::value,
                "Return type of getter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            fields.emplace_back(
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                !methodGetter ? nullptr : new GetterType( methodGetter ),
                !fieldSetter ? nullptr : new FieldSetter<ClassType, FieldType, false>( fieldSetter )  
            );

            fields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType, typename SetterArgumentType>
        void TypeData::AddField(
            const std::string &name,
            typename FieldGetter<ClassType, FieldType, false>::Signature fieldGetter,
            void (ClassType::*methodSetter)(SetterArgumentType),
            const MetaManager::Initializer &meta
        )
        {
            typedef FieldSetter<ClassType, SetterArgumentType, true> SetterType;

            static_assert( std::is_same<typename std::decay<SetterArgumentType>::type, typename std::decay<FieldType>::type>::value,
                "Argument type of setter does not match field type. "
                "This results in undefined behavior! (Even if there exists a conversion constructor between the types)"
            );

            fields.emplace_back(
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                !fieldGetter ? nullptr : new FieldGetter<ClassType, FieldType, false>( fieldGetter ),
                !methodSetter ? nullptr : new SetterType( methodSetter )
            );

            fields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType>
        void TypeData::AddField(
            const std::string &name,
            typename FieldGetter<ClassType, FieldType, false>::Signature fieldGetter,
            typename FieldSetter<ClassType, FieldType, false>::Signature fieldSetter,
            const MetaManager::Initializer &meta
        )
        {
            fields.emplace_back(
                name,
                typeof( FieldType ),
                typeof( ClassType ),
                !fieldGetter ? nullptr : new FieldGetter<ClassType, FieldType, false>( fieldGetter ),
                !fieldSetter ? nullptr : new FieldSetter<ClassType, FieldType, false>( fieldSetter ) 
            );

            fields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType, typename GetterType, typename SetterType>
        void TypeData::AddStaticField(const std::string &name, GetterType getter, SetterType setter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<FieldType, true> GlobalGetterType;
            typedef GlobalSetter<FieldType, true> GlobalSetterType;

            staticFields.emplace_back(
                name,
                typeof( FieldType ),
                !getter ? nullptr : new GlobalGetterType(
                    reinterpret_cast<typename GlobalGetterType::Signature>( getter )
                ),
                !setter ? nullptr : new GlobalSetterType(
                    reinterpret_cast<typename GlobalSetterType::Signature>( setter )
                ),
                typeof( ClassType )
            );

            staticFields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType, typename GetterType>
        void TypeData::AddStaticField(const std::string &name, GetterType getter, FieldType *fieldSetter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<FieldType, true> GlobalGetterType;
            typedef GlobalSetter<FieldType, false> GlobalSetterType;

            staticFields.emplace_back(
                name,
                typeof( FieldType ),
                !getter ? nullptr : new GlobalGetterType(
                    reinterpret_cast<typename GlobalGetterType::Signature>( getter )
                ),
                !fieldSetter ? nullptr : new GlobalSetterType( fieldSetter ),
                typeof( ClassType )
            );

            staticFields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType, typename SetterType>
        void TypeData::AddStaticField(const std::string &name, FieldType *fieldGetter, SetterType setter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<FieldType, false> GlobalGetterType;
            typedef GlobalSetter<FieldType, true> GlobalSetterType;

            staticFields.emplace_back(
                name,
                typeof( FieldType ),
                !fieldGetter ? nullptr : new GlobalGetterType( fieldGetter ),
                !setter ? nullptr : new GlobalSetterType(
                    reinterpret_cast<typename GlobalSetterType::Signature>( setter )
                ),
                typeof( ClassType )
            );

            staticFields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FieldType>
        void TypeData::AddStaticField(const std::string &name, FieldType *fieldGetter, FieldType *fieldSetter, const MetaManager::Initializer &meta)
        {
            typedef GlobalGetter<FieldType, false> GlobalGetterType;
            typedef GlobalSetter<FieldType, false> GlobalSetterType;

            staticFields.emplace_back(
                name,
                typeof( FieldType ),
                !fieldGetter ? nullptr : new GlobalGetterType( fieldGetter ),
                !fieldSetter ? nullptr : new GlobalSetterType( fieldSetter ),
                typeof( ClassType )
            );

            staticFields.back( ).m_meta = meta;
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType>
        void TypeData::SetDestructor(void)
        {
            destructor = {
                typeof( ClassType ),
                new DestructorInvoker<ClassType>( )
            };
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename MethodType>
        void TypeData::AddMethod(
            const std::string &name,
            MethodType method,
            const MetaManager::Initializer &meta
        )
        {
            Method meth( name, method );

            meth.m_meta = meta;

            methods[ name ].emplace( meth.GetSignature( ), meth );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename FunctionType>
        void TypeData::AddStaticMethod(
            const std::string &name,
            FunctionType function,
            const MetaManager::Initializer &meta
        )
        {
            Function fn( name, function, typeof( ClassType ) );

            fn.m_meta = meta;

            staticMethods[ name ].emplace( fn.GetSignature( ), fn );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename EnumType>
        void TypeData::SetEnum(
            const std::string &name,
            const typename EnumContainer<EnumType>::Initializer &initializer
        )
        {
            enumeration = new EnumContainer<EnumType>( name, initializer );
        }
    }
}
