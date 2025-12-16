#include "testStructs.h"

std::string TestStateToString(TestState ts) {
    switch(ts) {
        case UNTESTED:
            return "----";
        case FAILED:
            return "FAIL";
        case ERROR:
            return "ERR";
        case INVALID:
            return "INVAL";
        case NO_VALUE:
            return "NOVAL";
        case PASSED:
            return "PASS";
        case SUCCEEDED:
            return "SUCC";
    }
    return "NAN";
}