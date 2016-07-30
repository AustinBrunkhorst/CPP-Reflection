#pragma once

#if defined(__clang__)

#define COMPILER_CLANG

#elif defined(__GNUC__) || defined(__GNUG__)

#define COMPILER_GNU

#elif defined(_MSC_VER) && !__INTEL_COMPILER

#define COMPILER_MSVC

#endif