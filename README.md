# OpenGL 1.x Test Suite (GL1XTS)
A OpenGL 1.0/1.1 Conformance Test Suite

This collection of tests exists as a super basic way to test a custom `libGL` implementation, passed in via `LD_PRELOAD=/path/to/libGL.so`

## Tests
- Checks if returned Parameters, such as `MAX TEXTURE SIZE` or the number of Projection Matrices meet the spec-defined minimum requirements
- TBD

## Required Functions
GL1XTS requires a few functions to correctly test the correctness of all behaviors. These are the absolute minimum functions one must implement correctly to test all other behaviors (TBD).
- -

## Resources
- [The OpenGL Graphics System Specification (Version 1.0)](https://registry.khronos.org/OpenGL/specs/gl/glspec10.pdf)
- [The OpenGL Graphics System Specification (Version 1.1)](https://registry.khronos.org/OpenGL/specs/gl/glspec11.pdf)