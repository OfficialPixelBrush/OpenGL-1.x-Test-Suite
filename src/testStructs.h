#include <string>

enum TestState {
    UNTESTED, // Not yet tested
    FAILED, // 
    SUCCEEDED, // Perfectly meets the spec
    INVALID, // Incorrect result
    ERROR, // 
    NO_VALUE, // No result
    PASSING // Technically wrong, but not accurate
};

struct TestResult {
    std::string reason = "";
    TestState state = UNTESTED;
};

struct TestEntry {
    std::string name;
    TestResult (*testPtr)();
    TestResult result;
};