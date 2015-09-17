#include "Precompiled.h"

#include "LanguageTypes/Invokable.h"

#include <Utils.h>

Invokable::Invokable(const Cursor &cursor)
    : m_returnType( cursor.GetReturnType( ).GetDisplayName( ) )
{
    auto type = cursor.GetType( );
    unsigned count = type.GetArgumentCount( );

    m_signature.clear( );

    for (unsigned i = 0; i < count; ++i)
    {
        auto argument = type.GetArgument( i );

        // we need to make sure we have the qualified namespace
        if (argument.GetKind( ) == CXType_Typedef)
        {
            auto declaration = argument.GetDeclaration( );

            auto parent = declaration.GetLexicalParent( );

            Namespace parentNamespace;

            // walk up to the root namespace
            while (parent.GetKind( ) == CXCursor_Namespace)
            {
                parentNamespace.emplace_back( parent.GetDisplayName( ) );

                parent = parent.GetLexicalParent( );
            }

            // add the display name as the end of the namespace
            parentNamespace.emplace_back( 
                argument.GetDisplayName( )
            );

            std::string qualifiedName;

            ursine::utils::Join( parentNamespace, "::", qualifiedName );

            m_signature.emplace_back( qualifiedName );
        }
        // it should already be qualified
        else
        {
            m_signature.emplace_back(
                argument.GetDisplayName( )
            );
        }
    }
}

TemplateData Invokable::compileSignatureTemplate(void) const
{
    TemplateData data { TemplateData::Type::List };

    auto argCount = m_signature.size( );

    for (unsigned i = 0; i < argCount; ++i)
    {
        TemplateData argument { TemplateData::Type::Object };

        argument[ "type" ] = m_signature[ i ];
        argument[ "index" ] = std::to_string( i );
        argument[ "isLast" ] = utils::TemplateBool( i == argCount - 1 );

        data << argument;
    }

    return data;
}