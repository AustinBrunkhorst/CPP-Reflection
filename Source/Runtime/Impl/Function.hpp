namespace ursine
{
    namespace meta
    {
        template<typename ReturnType, typename ...ArgTypes>
        Function::Function(
            const std::string &name, 
            ReturnType(*type)(ArgTypes...), 
            Invoker invoker, Type parentType
        )
            : Invokable( name )
            , m_parentType( parentType )
            , m_invoker( invoker )
        {
            TypeUnpacker<ArgTypes...>::Apply( m_signature );
        }

        ///////////////////////////////////////////////////////////////////////

        template<typename ...Args>
        Variant Function::Invoke(Args &&...args) const
        {
            ArgumentList arguments { std::forward<Args>( args )... };

            return InvokeVariadic( arguments );
        }
    }
}
