#include "tests.h"

std::vector<TestContainer> testList = {
    TestContainer{"TestDrawSingleColoredQuad","Attempts to draw a red quad","",reinterpret_cast<TestResult*>(TestDrawSingleColoredQuad)},
    TestContainer{"TestDrawMultiColoredQuad","Attempts to draw a multi-colored quad","",reinterpret_cast<TestResult*>(TestDrawMultiColoredQuad)}
};

float GetColorDistance(Col a, Col b) {
    float dr = (static_cast<float>(a.r) / 255.0f) - (static_cast<float>(b.r) / 255.0f);
    float dg = (static_cast<float>(a.g) / 255.0f) - (static_cast<float>(b.g) / 255.0f);
    float db = (static_cast<float>(a.b) / 255.0f) - (static_cast<float>(b.b) / 255.0f);
    float da = (static_cast<float>(a.a) / 255.0f) - (static_cast<float>(b.a) / 255.0f);

    return std::sqrt(dr*dr + dg*dg + db*db + da*da) / 2.0f;
}

TestResult TestPixel(int x, int y, Col c) {
    unsigned char dst[4];
    glFinish();
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    TestResult tr;
    Col oc = Col{dst[0],dst[1],dst[2],dst[3]};
    float dist = GetColorDistance(c,oc);
    tr.reason =
        c.str() + " / " + oc.str() + ": Diff " + std::to_string(dist * 100.0f) + "%";
    if (dist < 0.05) {
        tr.state = PASSED;
    } else {
        tr.state = FAILED;
    }
    return tr;
}

TestResult TestDrawSingleColoredQuad() {
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-1,-1);
        glVertex2f(1,-1);
        glVertex2f(1,1);
        glVertex2f(-1,1);
    glEnd();
    return TestPixel(0,0, Col(255,0,0,255));
}

TestResult TestDrawMultiColoredQuad() {
    glBegin(GL_QUADS);
        glColor3f(1,0,0);
        glVertex2f(-1,-1);
        glColor3f(0,1,0);
        glVertex2f(1,-1);
        glColor3f(0,0,1);
        glVertex2f(1,1);
        glColor3f(0,0,0);
        glVertex2f(-1,1);
    glEnd();
    return TestPixel(0,0, Col(255,0,0,255));
}