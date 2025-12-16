#include "testStructs.h"

bool color = true;

std::string ColoredTestStateToString(const TestState& ts) {
    if (!color) return TestStateToString(ts);

    switch (ts) {
        case UNTESTED:
            return "\x1b[1;41m" + TestStateToString(ts) + "\x1b[0m";
        case FAILED:
        case ERROR:
            return "\x1b[1;101m" + TestStateToString(ts) + "\x1b[0m";
        case INVALID:
        case NO_VALUE:
            return "\x1b[1;43m" + TestStateToString(ts) + "\x1b[0m";
        case PASSED:
            return "\x1b[1;42m" + TestStateToString(ts) + "\x1b[0m";
        default:
            return TestStateToString(ts);
    }
}

std::string TestStateToString(const TestState& ts) {
    switch(ts) {
        case UNTESTED:
            return "[----]";
        case FAILED:
            return "[FAIL]";
        case ERROR:
            return "[ERRO]";
        case INVALID:
            return "[INVA]";
        case NO_VALUE:
            return "[NOVA]";
        case PASSED:
            return "[PASS]";
    }
    return "NAN";
}

void IncrementTestCounter(TestCounter& tc, const TestState& ts) {
    tc.total++;
    switch(ts) {
        case UNTESTED:
            break;
        case FAILED:
            tc.failed++; break;
        case ERROR:
            tc.error++; break;
        case INVALID:
            tc.invalid++; break;
        case NO_VALUE:
            tc.no_value++; break;
        case PASSED:
            tc.passed++; break;
        default:
            break;
    }
}