#pragma once

#include <functional>
#include <string>
#include <ostream>

enum TestState {
    UNTESTED, // Not yet tested
    FAILED, // 
    ERROR, // 
    INVALID, // Incorrect result
    NO_VALUE, // No result
    PASSED, // Technically wrong, but not accurate
    SUCCEEDED, // Perfectly meets the spec
};

std::string TestStateToString(TestState ts);

struct TestResult {
    std::string reason = "";
    TestState state = UNTESTED;
    friend std::ostream& operator<<(std::ostream& os, const TestResult& tr) {
        os << "[" << TestStateToString(tr.state) << "]";
        return os;
    }
};

struct TestEntry {
    std::string name;
    std::function<TestResult()> testPtr;
    TestResult result;

    friend std::ostream& operator<<(std::ostream& os, const TestEntry& te) {
        os << te.result << "\t" <<  te.name;
        if (!te.result.reason.empty())
            os << "\t(" << te.result.reason << ")";
        return os;
    }
};

struct TestSection {
    std::string name;
    std::vector<TestEntry> tests;
};