cmake_minimum_required(VERSION 3.16)
project(gl1xts VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

add_executable(gl1xts
    src/main.cpp
    src/testHelper.cpp
    src/testStructs.cpp
    src/values.cpp
)

target_link_libraries(gl1xts PRIVATE OpenGL::GL)