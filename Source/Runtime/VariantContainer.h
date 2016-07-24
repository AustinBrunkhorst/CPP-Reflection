/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** VariantContainer.h
** --------------------------------------------------------------------------*/

#pragma once

#include "VariantBase.h"

#include "MetaTraits.h"

#include "Object.h"

#define DEFAULT_TYPE_HANDLER(typeName)                                                           \
    template<typename U = T>                                                                     \
    typeName get##typeName(                                                                      \
        typename std::enable_if<                                                                 \
            !std::is_convertible<typename meta_traits::TypeOrEnumType<U>::type, typeName>::value \
        >::type* = nullptr                                                                       \
    ) const;                                                                                     \
    template<typename U = T>                                                                     \
    typeName get##typeName(                                                                      \
        typename std::enable_if<                                                                 \
            std::is_convertible<typename meta_traits::TypeOrEnumType<U>::type, typeName>::value  \
        >::type* = nullptr                                                                       \
    ) const;                                                                                     \

namespace ursine
{
    namespace meta
    {
        template<typename T>
        class VariantContainer : public VariantBase
        {
        public:
            typedef typename std::remove_reference<T>::type NonRefType;

            VariantContainer(const NonRefType &value);
            VariantContainer(const NonRefType &&value);

            Type GetType(void) const override;

            void *GetPtr(void) const override;

            int ToInt(void) const override;
            bool ToBool(void) const override;
            float ToFloat(void) const override;
            double ToDouble(void) const override;
            std::string ToString(void) const override;

            VariantBase *Clone(void) const override;

            void OnSerialize(Json::object &output) const override;
            void OnDeserialize(const Json &input) override;
        private:
            friend class Variant;

            T m_value;

            VariantContainer &operator=(const VariantContainer &rhs) = delete;

            DEFAULT_TYPE_HANDLER( int );
            DEFAULT_TYPE_HANDLER( bool );
            DEFAULT_TYPE_HANDLER( float );
            DEFAULT_TYPE_HANDLER( double );

            template<typename U = T>             
            std::string getString(
                typename std::enable_if<                 
                    !std::is_arithmetic<U>::value 
                >::type* = nullptr                       
            ) const;          

            template<typename U = T>                     
            std::string getString(
                typename std::enable_if<                 
                    std::is_arithmetic<U>::value
                >::type* = nullptr                       
            ) const;             

            template<typename U = T>
            void onSerialize(
                Json::object &output,
                typename std::enable_if<
                    !std::is_pointer<U>::value && std::is_base_of<Object, U>::value
                >::type* = nullptr
            ) const;

            template<typename U = T>
            void onSerialize(
                Json::object &output,
                typename std::enable_if<
                    std::is_pointer<U>::value || !std::is_base_of<Object, U>::value
                >::type* = nullptr
            ) const;

            template<typename U = T>
            void onDeserialize(
                const Json &input,
                typename std::enable_if<
                    !std::is_pointer<U>::value && std::is_base_of<Object, U>::value
                >::type* = nullptr
            );

            template<typename U = T>
            void onDeserialize(
                const Json &input,
                typename std::enable_if<
                    std::is_pointer<U>::value || !std::is_base_of<Object, U>::value
                >::type* = nullptr
            );
        };
    }
}

#undef DEFAULT_TYPE_HANDLER

#include "Impl/VariantContainer.hpp"
#include "Impl/VariantContainerStandardTypes.hpp"