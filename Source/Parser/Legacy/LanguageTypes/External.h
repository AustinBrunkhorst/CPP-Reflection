/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** External.h
** --------------------------------------------------------------------------*/

#pragma once

#include "LanguageTypes/Class.h"

class External : public Class
{
public:
    External(const Cursor &cursor);

    bool ShouldCompile(void) const override;
};