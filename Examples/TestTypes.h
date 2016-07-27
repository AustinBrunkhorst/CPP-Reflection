#pragma once

#include <Meta.h>

#include "TestProperties.h"

#include <string>
#include <vector>

#include <Array.h>

enum TestEnum
{
    One,
    Two,
    Three,
    Four,
    Five,
    Eighty = 80
} Meta(Enable);

struct SoundEffect
{
    Meta(Range(0.0f, 100.0f), Slider(SliderType::Horizontal))
    float volume;

    void Load(const std::string &filename)
    {
        std::cout << "Loaded sound effect \"" << filename << "\"." << std::endl;
    }
} Meta(Enable);

struct ComplexType
{
    std::string stringValue;
    int intValue;
    float floatValue;
    double doubleValue;
    
    SoundEffect soundEffect;

    ursine::Array<int> arrayValue;

    TestEnum enumValue;

    ComplexType(void) = default;
} Meta(Enable);