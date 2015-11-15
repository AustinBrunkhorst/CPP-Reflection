/* ----------------------------------------------------------------------------
** © 201x Austin Brunkhorst, All Rights Reserved.
**
** Templates.h
** --------------------------------------------------------------------------*/

#pragma once

#define EXT ".mustache"

const auto kTemplateHeader                      = "header" EXT;
const auto kTemplateSource                      = "source" EXT;
                                                
const auto kPartialFunctionInvocation           = "function-invocation" EXT;
const auto kPartialConstructorInvocation        = "constructor-invocation" EXT;
const auto kPartialDynamicConstructorInvocation = "dynamic-constructor-invocation" EXT;
const auto kPartialMethodInvocation             = "method-invocation" EXT;
                                                
const auto kPartialGlobalGetter                 = "global-getter" EXT;
const auto kPartialGlobalSetter                 = "global-setter" EXT;
                                                
const auto kPartialFieldGetter                  = "field-getter" EXT;
const auto kPartialFieldSetter                  = "field-setter" EXT;
                                                
const auto kPartialMetaInitializerList          = "meta-initializer-list" EXT;

#undef EXT