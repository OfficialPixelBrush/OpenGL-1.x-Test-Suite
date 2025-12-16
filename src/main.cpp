#include <iostream>
#include <GL/gl.h>

#include "testStructs.h"
#include "defines.h"
#include <vector>

std::vector<TestEntry> tests;

void RegisterTest(const std::string& name, TestResult (*testPtr)()) {
    TestEntry te{name, testPtr, {}};
    tests.push_back(te);
}

bool TestIntegerMin(GLenum value, int desired) {
    GLint number = 0;
    glGetIntegerv(value, &number);
    return number >= desired;
}

int main() {
    std::cout << TestInteger(GL_MAX_LIGHTS, MINIMUM_MAX_LIGHTS) << "\n";
    return 0;
}