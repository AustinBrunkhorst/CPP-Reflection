/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** External.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "External.h"

External::External(const Cursor &cursor)
    : Class( cursor, { } )
{
    
}

bool External::ShouldCompile(void) const
{
    return true;
}