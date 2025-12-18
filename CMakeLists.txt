cmake_minimum_required(VERSION 3.16)
project(gl1xts VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

add_executable(gl1xts
    src/main.cpp
    src/testHelper.cpp
    src/testStructs.cpp
    src/lists/values.cpp
    src/lists/functions.cpp
    src/lists/tests.cpp
)

target_link_libraries(gl1xts
    PRIVATE
    GL
    GLX
    X11
)