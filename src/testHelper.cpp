#include "testHelper.h"
#include "testStructs.h"
#include <GL/gl.h>
#include <GL/glext.h>

TestResult TestValueMin(GLenum pname, int64_t desired, GLenum type) {
    GLboolean boolTest = 0;
    GLint intTest = 0;
    GLfloat floatTest = 0.0f;
    switch(type) {
        case GL_BOOL:
            glGetBooleanv(pname, &boolTest); break;
        case GL_FLOAT:
            glGetFloatv(pname, &floatTest); break;
        case GL_INT:
            glGetIntegerv(pname, &intTest); break;
    }
    
    TestResult tr;
    if (type == GL_BOOL) {
        if (boolTest != bool(desired)) {
            tr.reason = "Non-matching " + std::to_string(boolTest) + "/" + std::to_string(bool(desired));
            tr.state = FAILED;
            return tr;
        }
    }
    if (type == GL_FLOAT) {
        float desiredFloat = std::bit_cast<float>(int(desired));
        if (floatTest < desiredFloat) {
            tr.reason = "Below minimum " + std::to_string(floatTest) + "/" + std::to_string(desiredFloat);
            tr.state = FAILED;
            return tr;
        }
        if (floatTest > desiredFloat) {
            tr.reason = "Exceeded minimum " + std::to_string(floatTest) + "/" + std::to_string(desiredFloat);
        }
    }
    if (type == GL_INT) {
        if (intTest < desired) {
            tr.reason = "Below minimum " + std::to_string(intTest) + "/" + std::to_string(desired);
            tr.state = FAILED;
            return tr;
        }
        if (intTest > desired) {
            tr.reason = "Exceeded minimum " + std::to_string(intTest) + "/" + std::to_string(desired);
        }
    }
    tr.state = PASSED;
    return tr;
}

TestResult TestFunctionExistence(void* funcPtr) {
    TestResult tr;
    if (funcPtr == nullptr) {
        tr.reason = "Function does not exist";
        tr.state = FAILED;
        return tr;
    }
    tr.state = PASSED;
    return tr;
}