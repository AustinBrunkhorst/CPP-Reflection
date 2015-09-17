/* ----------------------------------------------------------------------------
** Team Bear King
** © 201x DigiPen Institute of Technology, All Rights Reserved.
**
** Argument.h
**
** Author:
** - Austin Brunkhorst - a.brunkhorst@digipen.edu
** --------------------------------------------------------------------------*/

#pragma once

#include <vector>

namespace ursine
{
    namespace meta
    {
        class Type;
        class Variant;

        class Argument
        {
        public:
            Argument(void);
            Argument(const Argument &rhs);
            Argument(Variant &obj);
            Argument(const Variant &obj);

            template<typename T>
            Argument(const T &data);

            template<typename T>
            Argument(T &data);

            Argument &operator=(const Argument &rhs);

            Type GetType(void) const;

            void *GetPtr(void) const;

            template<typename T>
            T &GetValue(void) const;

        private:
            const Type m_type;
            const void *m_data;
        };
    }
}

#include "Impl/Argument.hpp"