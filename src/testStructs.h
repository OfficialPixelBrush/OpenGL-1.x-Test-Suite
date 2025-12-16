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
    PASSED, // Meets or exceeds the spec
};

std::string ColoredTestStateToString(const TestState& ts);
std::string TestStateToString(const TestState& ts);

struct TestCounter {
    int total = 0;
    int failed = 0;
    int error = 0;
    int invalid = 0;
    int no_value = 0;
    int passed = 0;

    TestCounter operator+(const TestCounter& o) const {
        return TestCounter{
            total + o.total,
            failed + o.failed,
            error + o.error,
            invalid + o.invalid,
            no_value + o.no_value,
            passed + o.passed
        };
    }
};

void IncrementTestCounter(TestCounter& tc, const TestState& ts);

struct TestResult {
    std::string reason = "";
    TestState state = UNTESTED;
    friend std::ostream& operator<<(std::ostream& os, const TestResult& tr) {
        os << ColoredTestStateToString(tr.state);
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