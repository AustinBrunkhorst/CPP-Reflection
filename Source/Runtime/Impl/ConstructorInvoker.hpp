/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ConstructorInvoker.hpp
** --------------------------------------------------------------------------*/

#pragma once

#include "../Common/Logging.h"

#include "../Variant.h"
#include "../ArgumentConfig.h"
#include "../Argument.h"

namespace ursine
{
    namespace meta
    {
        ////////////////////////////////////////////////////////////////THIS_ARG_COUNT///////
        // Non Dynamic
        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, bool IsObjectWrapped, typename ...ArgTypes>
        class ConstructorInvoker<ClassType, false, IsObjectWrapped, ArgTypes...> : public ConstructorInvokerBase
        {
        public:
            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Constructor has too many arguments. It's time to generate more overloads."
            );

            Variant Invoke(const ArgumentList &arguments) override
            {
                UAssert( arguments.size( ) == THIS_ARG_COUNT,
                    "Invalid constructor arguments.\nExpected %i args but got %i.",
                    THIS_ARG_COUNT,
                    arguments.size( )
                );

                return invoke<void, ArgTypes...>( arguments );
            }

        private:
            template<typename _>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType( );
            }

            template<typename _, typename A1>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( )
                );
            }

            template<typename _, typename A1, typename A2>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( ),
                    arguments[ 9 ].GetValue<A10>( )
                );
            }
        };

        ///////////////////////////////////////////////////////////////////////
        // Dynamic, Non Wrapped
        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ...ArgTypes>
        class ConstructorInvoker<ClassType, true, false, ArgTypes...> : public ConstructorInvokerBase
        {
        public:

            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Constructor has too many arguments. It's time to generate more overloads."
            );

            Variant Invoke(const ArgumentList &arguments) override
            {
                UAssert( arguments.size( ) == THIS_ARG_COUNT,
                    "Invalid constructor arguments.\nExpected %i args but got %i.",
                    THIS_ARG_COUNT,
                    arguments.size( )
                );

                return invoke<void, ArgTypes...>( arguments );
            }

        private:
            template<typename _>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType( );
            }

            template<typename _, typename A1>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( )
                );
            }

            template<typename _, typename A1, typename A2>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( )
                );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            Variant invoke(const ArgumentList &arguments) const
            {
                return new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( ),
                    arguments[ 9 ].GetValue<A10>( )
                );
            }
        };

        ///////////////////////////////////////////////////////////////////////
        // Dynamic, Wrapped
        ///////////////////////////////////////////////////////////////////////

        template<typename ClassType, typename ...ArgTypes>
        class ConstructorInvoker<ClassType, true, true, ArgTypes...> : public ConstructorInvokerBase
        {
        public:
            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Constructor has too many arguments. It's time to generate more overloads."
            );

            Variant Invoke(const ArgumentList &arguments) override
            {
                UAssert( arguments.size( ) == THIS_ARG_COUNT,
                    "Invalid constructor arguments.\nExpected %i args but got %i.",
                    THIS_ARG_COUNT,
                    arguments.size( )
                );

                return invoke<void, ArgTypes...>( arguments );
            }

        private:
            template<typename _>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType( ) );
            }

            template<typename _, typename A1>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( )
                ) );
            }

            template<typename _, typename A1, typename A2>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( )
                ) );
            }

            template<typename _, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            Variant invoke(const ArgumentList &arguments) const
            {
                return ObjectVariant( new ClassType(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( ),
                    arguments[ 7 ].GetValue<A8>( ),
                    arguments[ 8 ].GetValue<A9>( ),
                    arguments[ 9 ].GetValue<A10>( )
                ) );
            }
        };
    }
}
