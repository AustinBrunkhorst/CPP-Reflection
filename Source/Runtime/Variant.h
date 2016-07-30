/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Variant.h
** --------------------------------------------------------------------------*/

#pragma once

#include "VariantBase.h"
#include "VariantPolicy.h"

#include "Array.h"
#include "TypeConfig.h"

#include "Object.h"

#define DISABLE_VARIANT                  \
    typename std::enable_if<             \
        !std::is_same<Variant, T>::value \
    >::type*                             \

#define DISABLE_VARIANT_DECL DISABLE_VARIANT = nullptr

#define DISABLE_ARGUMENT                  \
    typename std::enable_if<              \
        !std::is_same<Argument, T>::value \
    >::type*                              \

#define DISABLE_ARGUMENT_DECL DISABLE_ARGUMENT = nullptr

#define DISABLE_CONST            \
    typename std::enable_if<     \
        !std::is_const<T>::value \
    >::type*                     \

#define DISABLE_CONST_DECL DISABLE_CONST = nullptr

namespace ursine
{
    namespace meta
    {
        class Argument;
        class ArrayWrapper;

        class Variant
        {
        public:
            Variant(void);

            // Given a type that inherits from a meta::Object and
            // supplied with the "WrapObject" policy, use the object wrapper
            // variant base 
            template<typename T>
            Variant(
                T *data, 
                variant_policy::WrapObject,
                typename std::enable_if< 
                    std::is_base_of<Object, T>::value 
                >::type* = nullptr
            );

            template<typename T>
            Variant(
                T &data,
                DISABLE_VARIANT_DECL
            );

            template<typename T>
            Variant(
                T &data,
                variant_policy::NoCopy,
                DISABLE_VARIANT_DECL
            );

            // non-const r-value references, excluding other variants and arguments
            template<typename T>
            Variant(T &&data,
                DISABLE_VARIANT_DECL,
                DISABLE_ARGUMENT_DECL,
                DISABLE_CONST_DECL
            );

            // array types (non-const)
            template<typename T>
            Variant(Array<T> &rhs);

            // array types (const)
            template<typename T>
            Variant(const Array<T> &rhs);

            // r-value array types (non-const)
            template<typename T>
            Variant(Array<T> &&rhs);

            // r-value array types (const)
            template<typename T>
            Variant(const Array<T> &&rhs);

            // copy constructor
            Variant(const Variant &rhs);

            // r-value
            Variant(Variant &&rhs);

            ~Variant(void);

            template<typename T>
            Variant &operator=(T &&rhs);

            Variant &operator=(const Variant &rhs);

            Variant &operator=(Variant &&rhs);

            operator bool(void) const;

            Type GetType(void) const;
            ArrayWrapper GetArray(void) const;

            void Swap(Variant &other);

            int ToInt(void) const;
            bool ToBool(void) const;
            float ToFloat(void) const;
            double ToDouble(void) const;
            std::string ToString(void) const;

            Json SerializeJson(void) const;

            template<typename T>
            T &GetValue(void) const;

            bool IsValid(void) const;
            bool IsConst(void) const;
            bool IsArray(void) const;

        private:
            friend class Type;
            friend class Argument;
            friend class Destructor;

            void *getPtr(void) const;

            bool m_isConst;

            VariantBase *m_base;
        };
    }
}

#include "Impl/Variant.hpp"

#undef DISABLE_VARIANT
#undef DISABLE_VARIANT_DECL
#undef DISABLE_ARGUMENT
#undef DISABLE_ARGUMENT_DECL
#undef DISABLE_CONST
#undef DISABLE_CONST_DECL
