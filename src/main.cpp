#include <iostream>
#include <GL/gl.h>

#include "testStructs.h"
#include "defines.h"
#include <vector>

std::vector<TestEntry> tests;

void RegisterTest(std::string name, void* testPtr) {
    tests.push_back(TestEntry {
        name, testPtr
    });
}

int TestMinimumValues() {
    int numberOfTests = 1;

    int maxLights = 0;
    glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
    if (maxLights == MINIMUM_MAX_LIGHTS) 
}

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}