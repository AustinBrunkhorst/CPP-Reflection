/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** DestructorInvoker.hpp
** --------------------------------------------------------------------------*/

namespace ursine
{
    namespace meta
    {
        template<typename ClassType>
        void DestructorInvoker<ClassType>::Invoke(const Variant& obj)
        {
            auto &instance = obj.GetValue<ClassType>( );

            instance.~ClassType( );
        }
    }
}
