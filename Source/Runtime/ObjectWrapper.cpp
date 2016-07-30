/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** ObjectWrapper.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "ObjectWrapper.h"
#include "Object.h"

#include "Type.h"

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

        void ObjectWrapper::OnSerialize(Json::object &output) const
        {
            m_object->OnSerialize( output );
        }

        void ObjectWrapper::OnDeserialize(const Json &input)
        {
            m_object->OnDeserialize( input );
        }
    }
}