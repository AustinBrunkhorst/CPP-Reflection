/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** VoidMethodInvoker.hpp
** --------------------------------------------------------------------------*/

#pragma once

namespace ursine
{
    namespace meta
    {
        template<typename ClassType, typename ...ArgTypes>
        class MethodInvoker<ClassType, void, ArgTypes...> : public MethodInvokerBase
        {
        public:
            typedef void (ClassType::*Signature)(ArgTypes...);
            typedef void (ClassType::*ConstSignature)(ArgTypes...) const;

            static_assert( THIS_ARG_COUNT <= MaxArgumentCount,
                "Method has too many arguments. It's time to generate more overloads."
            );

            MethodInvoker(Signature method)
                : m_method( reinterpret_cast<ConstSignature>( method ) ) { }

            MethodInvoker(ConstSignature method)
                : m_method( method ) { }

            Variant Invoke(Variant &obj, const ArgumentList &arguments) override
            {
                UAssert( arguments.size( ) == THIS_ARG_COUNT,
                    "Invalid method arguments.\nExpected %i args but got %i.",
                    THIS_ARG_COUNT,
                    arguments.size( )
                );

                invoke<void, ArgTypes...>( obj, arguments );

                return { };
            }

        private:
            template<typename X>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)( );
            }

            template<typename X, typename A1>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( )
                );
            }

            template<typename X, typename A1, typename A2>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( )
                );
            }

            template<typename X, typename A1, typename A2, typename A3>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( )
                );
            }

            template<typename X, typename A1, typename A2, typename A3, typename A4>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( )
                );
            }

            template<typename X, typename A1, typename A2, typename A3, typename A4, typename A5>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( )
                );
            }

            template<typename X, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( )
                );
            }

            template<typename X, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
                    arguments[ 0 ].GetValue<A1>( ),
                    arguments[ 1 ].GetValue<A2>( ),
                    arguments[ 2 ].GetValue<A3>( ),
                    arguments[ 3 ].GetValue<A4>( ),
                    arguments[ 4 ].GetValue<A5>( ),
                    arguments[ 5 ].GetValue<A6>( ),
                    arguments[ 6 ].GetValue<A7>( )
                );
            }

            template<typename X, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
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

            template<typename X, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
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

            template<typename X, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
            void invoke(Variant &obj, const ArgumentList &arguments)
            {
                auto &instance = obj.GetValue<ClassType>( );

                (instance.*m_method)(
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

            ConstSignature m_method;
        };
    }
}