#pragma once

#include <GL/gl.h>
#include <string>
#include "../testStructs.h"
struct GenericContainer {
    std::string name = "";
    std::string description = "";
    std::string section = "";
};

struct FunctionContainer : public GenericContainer {
    // Function name must be equal to name
    void* funcPtr;
};

struct ValueContainer : public GenericContainer {
    GLenum type = GL_INT;
    int64_t minimumValue = 0;
    GLenum glEnum;
};

struct TestContainer : public GenericContainer {
    TestResult* funcPtr;
};