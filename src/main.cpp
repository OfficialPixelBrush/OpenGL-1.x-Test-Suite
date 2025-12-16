#include <exception>
#include <iostream>
#include <GL/gl.h>

#include "testStructs.h"
#include "values.h"
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

std::pair<int,int> RunSection(const TestSection& ts) {
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
        if (t.result.state == PASSED || t.result.state == SUCCEEDED) {
            testsPassed++;
        }
    }
    return std::pair<int,int>{testsPassed,ts.tests.size()};
}

void RunAllTests() {
    int testsPassed = 0;
    int totalTestsRun = 0;
    for (auto ts : testSections) {
        std::pair<int,int> res = RunSection(ts);
        testsPassed += res.first;
        totalTestsRun += res.second;
    }
    std::cout << testsPassed << "/" << totalTestsRun << " PASSED TESTS" << std::endl;
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
    
    RunAllTests();
    return 0;
}