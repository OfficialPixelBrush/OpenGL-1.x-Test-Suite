#include <X11/Xlib.h>
#include <GL/glx.h>
#include <unistd.h>
#include <exception>
#include <iostream>
#include <GL/gl.h>

#include "lists/tests.h"
#include "testStructs.h"
#include "lists/functions.h"
#include "lists/values.h"
#include <string>
#include <vector>

#include "testHelper.h"

#define WINDOW_WIDTH 256
#define WINDOW_HEIGHT 256

#define WAIT_TIME_BETWEEN_TEST 10000

std::vector<TestSection> testSections;
Display* dpy;
Window win;

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
        glXSwapBuffers(dpy, win);
        usleep(WAIT_TIME_BETWEEN_TEST);
    }
    std::cout << "Passed Tests: " << tc.passed << "/" << tc.total << std::endl;
    return tc;
}

void RunAllTests() {
    TestCounter totalTC;
    for (auto ts : testSections) {
        TestCounter resTC = RunSection(ts);
        totalTC = totalTC + resTC;
    }
    std::cout << "\n--- RESULTS --- \n";
    std::cout << "Total Passed Tests: " << " " << totalTC.passed << "/" << totalTC.total << std::endl;
}

int InitWindow() {
    dpy = XOpenDisplay(nullptr);
    if (!dpy) return 2;

    static int attribs[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None };
    int screen = DefaultScreen(dpy);
    XVisualInfo* vi = glXChooseVisual(dpy, screen, attribs);
    if (!vi) { XCloseDisplay(dpy); return 3; }

    Colormap cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    win = XCreateWindow(dpy, RootWindow(dpy, vi->screen),
                            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                            vi->depth, InputOutput, vi->visual,
                            CWColormap | CWEventMask, &swa);
    XMapWindow(dpy, win);

    GLXContext ctx = glXCreateContext(dpy, vi, nullptr, True);
    if (!ctx) { XDestroyWindow(dpy, win); XCloseDisplay(dpy); return 4; }
    glXMakeCurrent(dpy, win, ctx);
    return 0;
}

using FuncType = TestResult(*)();

int main() {
    InitWindow();

    RegisterSection("Required Implementation Dependent Values");
    for (auto idv : implementationDependentValuesRequired) {
        RegisterTest(idv.name, [idv]() {
            return TestValueMin(idv.glEnum, idv.minimumValue, idv.type);
        });
    }
    RegisterSection("Supported Feature Values");
    for (auto idv : implementationDependentValuesOptional) {
        RegisterTest(idv.name, [idv]() {
            return TestValueMin(idv.glEnum, idv.minimumValue, idv.type);
        });
    }
    RegisterSection("Function Implementation Check");
    for (auto f : functionList) {
        RegisterTest(f.name, [f]() {
            return TestFunctionExistence(f.funcPtr);
        });
    }
    RegisterSection("Functionality Check");
    for (auto t : testList) {
        RegisterTest(t.name, [t]() {
            FuncType f = reinterpret_cast<FuncType>(t.funcPtr);
            return f();
        });
    }
    
    RunAllTests();
    return 0;
}