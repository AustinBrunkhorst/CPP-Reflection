/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Templates.h
** --------------------------------------------------------------------------*/

#pragma once

#define EXT ".mustache"

const auto kTemplateModuleHeader       = "module-header" EXT;
const auto kTemplateModuleSource       = "module-source" EXT;
const auto kTemplateModuleFileHeader   = "module-file-header" EXT;
const auto kTemplateModuleFileSource   = "module-file-source" EXT;
        
const auto kPartialGlobalGetter        = "global-getter" EXT;
const auto kPartialGlobalSetter        = "global-setter" EXT;
                                       
const auto kPartialFieldGetter         = "field-getter" EXT;
const auto kPartialFieldSetter         = "field-setter" EXT;
                                       
const auto kPartialMetaInitializerList = "meta-initializer-list" EXT;

#undef EXT