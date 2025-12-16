#include <exception>
#include <iostream>
#include <GL/gl.h>

#include "testStructs.h"
#include "lists/functions.h"
#include "lists/values.h"
#include <string>
#include <vector>

#include "testHelper.h"

std::vector<TestSection> testSections;

void RegisterSection(const std::string& name) {
    TestSection te{name};
    testSections.push_back(te);
}

void RegisterTest(const std::string& name, std::function<TestResult()> testPtr) {
    TestEntry te{name, testPtr, {}};
    testSections.back().tests.push_back(te);
}

TestCounter RunSection(const TestSection& ts) {
    TestCounter tc;
    std::cout << "--- " << ts.name << " --- \n";
    int testsPassed = 0;
    for (auto t : ts.tests) {
        try {
            t.result = t.testPtr();
        } catch (std::exception& e) {
            t.result.state = ERROR;
            t.result.reason = e.what();
        }
        std::cout << t << "\n";
        IncrementTestCounter(tc, t.result.state);
    }
    std::cout << "Passed Tests: " << tc.passed+tc.success << "/" << tc.total << std::endl;
    return tc;
}

void RunAllTests() {
    TestCounter totalTC;
    for (auto ts : testSections) {
        TestCounter resTC = RunSection(ts);
        totalTC = totalTC + resTC;
    }
    std::cout << "\n--- RESULTS --- \n";
    std::cout << "Total Passed Tests: " << " " << totalTC.passed+totalTC.success << "/" << totalTC.total << std::endl;
}

int main() {
    RegisterSection("Required Implementation Dependent Values");
    for (auto idv : implementationDependentValuesRequired) {
        RegisterTest(idv.name, [idv]() {
            return TestValueMin(idv.glEnum, idv.minimumValue, idv.type);
        });
    }
    RegisterSection("Optional Implementation Dependent Values");
    for (auto idv : implementationDependentValuesOptional) {
        RegisterTest(idv.name, [idv]() {
            return TestValueMin(idv.glEnum, idv.minimumValue, idv.type);
        });
    }
    RegisterSection("Function Checking");
    std::string name = "glBegin";
    for (auto f : functionList) {
        RegisterTest(f.name, [f]() {
            return TestFunctionExistence(f.funcPtr);
        });
    }
    
    RunAllTests();
    return 0;
}