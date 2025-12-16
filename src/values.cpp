#include "values.h"
#include <GL/gl.h>
#include <string>

std::vector<ValueContainer> implementationDependentValuesRequired = {
    ValueContainer{ "MAX_LIGHTS","Maximum number of lights","2.13.1",GL_INT,8, GL_MAX_LIGHTS },
    ValueContainer{ "MAX_CLIP_PLANES","Maximum number of user clipping planes","2.11",GL_INT,6, GL_MAX_CLIP_PLANES },
    ValueContainer{ "MAX_MODELVIEW_STACK_DEPTH","Maximum model-viewstack depth","2.10.2",GL_INT,32, GL_MAX_MODELVIEW_STACK_DEPTH },
    ValueContainer{ "MAX_PROJECTION_STACK_DEPTH","Maximum projection matrix stack depth","2.10.2",GL_INT,2, GL_MAX_PROJECTION_STACK_DEPTH },
    ValueContainer{ "MAX_TEXTURE_STACK_DEPTH","Maximum number depth of texture matrix stack","2.10.2",GL_INT,2, GL_MAX_PROJECTION_STACK_DEPTH },
};


std::vector<ValueContainer> implementationDependentValuesOptional = {
    ValueContainer{ "RGBA_MODE","True if color buffers store rgba","2.7",GL_BOOL,1, GL_RGBA_MODE },
};

std::string TypeToString(ValueContainer vc) {
    switch(vc.type) {
        case GL_BOOL:
            return std::to_string(bool(vc.minimumValue));
        case GL_BYTE:
            return std::to_string((int(vc.minimumValue) & 0xFF));
        case GL_SHORT:
            return std::to_string((int(vc.minimumValue) & 0xFFFF));
        case GL_INT:
            return std::to_string((int(vc.minimumValue) & 0xFFFFFFFF));
        case GL_FLOAT:
            return std::to_string(std::bit_cast<float>(int(vc.minimumValue)));
        case GL_DOUBLE:
            return std::to_string(std::bit_cast<double>(vc.minimumValue));
        default:
            return "Invalid";
    }
}