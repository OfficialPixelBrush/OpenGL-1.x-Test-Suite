#pragma once

#include <GL/gl.h>
#include "containers.h"
#include "../testStructs.h"
#include <vector>
#include <cmath>

extern std::vector<TestContainer> testList;

TestResult TestDrawSingleColoredQuad();
TestResult TestDrawMultiColoredQuad();