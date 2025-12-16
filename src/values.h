#pragma once

#include <GL/gl.h>
#include <string>
#include <vector>

// Minimum values
#define MINIMUM_MAX_LIGHTS 8
#define MINIMUM_MAX_CLIP_PLANES 6
#define MINIMUM_MAX_MODELVIEW_STACK_DEPTH 32
#define MINIMUM_MAX_PROJETION_STACK_DEPTH 2
#define MINIMUM_MAX_TEXTURE_STACK_DEPTH 2
#define MINIMUM_SUBPIXEL_BITS 4
#define MINIMUM_MAX_TEXTURE_SIZE 64
#define MINIMUM_MAX_PIXEL_MAP_TABLE 32
#define MINIMUM_MAX_NAME_STACK_DEPTH 64
#define MINIMUM_MAX_LIST_NESTING 64
#define MINIMUM_MAX_EVAL_ORDER 8
#define MINIMUM_MAX_ATTRIB_STACK_DEPTH 16
#define MINIMUM_MAX_CLIENT_ATTRIB_STACK_DEPTH 16
#define MINIMUM_AUX_BUFFERS 0

struct ValueContainer {
    std::string name = "";
    std::string description = "";
    std::string section = "";
    GLenum type = GL_INT;
    int64_t minimumValue = 0;
    GLenum glEnum;
};

std::string TypeToString(ValueContainer vc);

extern std::vector<ValueContainer> implementationDependentValuesRequired;
extern std::vector<ValueContainer> implementationDependentValuesOptional;