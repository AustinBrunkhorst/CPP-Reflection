#pragma once

#include <Meta.h>

enum class SliderType
{
    Horizontal,
    Vertical
} Meta(Enable);

struct Slider : ursine::meta::MetaProperty
{
    META_OBJECT;

    SliderType type;

    Slider(SliderType type)
        : type(type) { }
} Meta(Enable);

struct Range : ursine::meta::MetaProperty
{
    META_OBJECT;

    float min, max;

    Range(float min, float max)
        : min(min)
        , max(max) { }
} Meta(Enable);