#include "testHelper.h"
#include "testStructs.h"
#include <GL/gl.h>
#include <GL/glext.h>

TestResult TestValueMin(GLenum pname, int64_t desired, GLenum type) {
    GLboolean boolTest = 0;
    GLint intTest = 0;
    switch(type) {
        case GL_BOOL:
            glGetBooleanv(pname, &boolTest); break;
        case GL_INT:
            glGetIntegerv(pname, &intTest); break;
    }
    
    TestResult tr;
    if (type == GL_BOOL) {
        if (boolTest != desired) {
            tr.reason = "Non-matching " + std::to_string(boolTest) + "/" + std::to_string(bool(desired));
            tr.state = FAILED;
            return tr;
        }
    } else {
        if (intTest >= desired) {
            tr.reason = "Exceeded minimum " + std::to_string(intTest) + "/" + std::to_string(desired);
            tr.state = PASSED;
            return tr;
        }
        if (intTest < desired) {
            tr.reason = "Below minimum " + std::to_string(intTest) + "/" + std::to_string(desired);
            tr.state = FAILED;
            return tr;
        }
    }
    tr.state = SUCCEEDED;
    return tr;
}

TestResult TestFunctionExistence(void* funcPtr) {
    TestResult tr;
    if (funcPtr == nullptr) {
        tr.reason = "Function does not exist";
        tr.state = FAILED;
        return tr;
    }
    tr.state = SUCCEEDED;
    return tr;
}