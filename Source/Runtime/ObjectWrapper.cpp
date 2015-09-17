#include "UrsinePrecompiled.h"

#include "ObjectWrapper.h"

namespace ursine
{
    namespace meta
    {
        ObjectWrapper::ObjectWrapper(Object *instance)
            : m_object( instance )
        {
        }

        Type ObjectWrapper::GetType(void) const
        {
            return m_object->GetType( );
        }

        void *ObjectWrapper::GetPtr(void) const
        {
            return m_object;
        }

        int ObjectWrapper::ToInt(void) const
        {
            return int( );
        }

        bool ObjectWrapper::ToBool(void) const
        {
            return bool( );
        }

        float ObjectWrapper::ToFloat(void) const
        {
            return float( );
        }

        double ObjectWrapper::ToDouble(void) const
        {
            return double( );
        }

        std::string ObjectWrapper::ToString(void) const
        {
            return std::string( );
        }

        VariantBase *ObjectWrapper::Clone(void) const
        {
            return new ObjectWrapper( m_object );
        }
    }
}