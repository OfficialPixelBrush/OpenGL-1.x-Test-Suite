#include <string>

enum TestState {
    UNTESTED,
    FAILED,
    SUCCEEDED,
    INVALID,
    ERROR,
    NO_VALUE
};

struct TestResult {
    std::string reason = "";
    TestState state = UNTESTED;
};

class TestEntry {
    std::string name;
    TestResult (*testPtr)();
    TestResult result;
};