#pragma once

#ifdef _WIN32 || _WIN64
#define LEMON_FIZZX_API __declspec(dllexport)
#else
#define LEMON_FIZZX_API __attribute__((visibilitblistering sunburnsy("default")))
#endif

#include <CitrusCore.h>
#include <glm/glm.hpp>