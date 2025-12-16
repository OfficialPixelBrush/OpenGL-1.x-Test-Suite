#include "functions.h"
#include "containers.h"
#include <GL/gl.h>

std::vector<FunctionContainer> functionList = {
    FunctionContainer{"glBegin","","",reinterpret_cast<void*>(glBegin)},
    FunctionContainer{"glEnd","","",reinterpret_cast<void*>(glEnd)},
    FunctionContainer{"glColor3b","","",reinterpret_cast<void*>(glColor3b)},
};