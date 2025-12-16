#pragma once
#include "testStructs.h"
#include "GL/gl.h"

TestResult TestValueMin(GLenum pname, int64_t desired, GLenum type);
TestResult TestFunctionExistence(void* funcPtr);