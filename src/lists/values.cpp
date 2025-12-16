#include "values.h"
#include <GL/gl.h>
#include <string>

// Values
std::vector<ValueContainer> implementationDependentValuesRequired = {
    ValueContainer{ "MAX_LIGHTS","Maximum number of lights","2.13.1",GL_INT,8, GL_MAX_LIGHTS },
    ValueContainer{ "MAX_CLIP_PLANES","Maximum number of user clipping planes","2.11",GL_INT,6, GL_MAX_CLIP_PLANES },
    ValueContainer{ "MAX_MODELVIEW_STACK_DEPTH","Maximum model-viewstack depth","2.10.2",GL_INT,32, GL_MAX_MODELVIEW_STACK_DEPTH },
    ValueContainer{ "MAX_PROJECTION_STACK_DEPTH","Maximum projection matrix stack depth","2.10.2",GL_INT,2, GL_MAX_PROJECTION_STACK_DEPTH },
    ValueContainer{ "MAX_TEXTURE_STACK_DEPTH","Maximum number depth of texture matrix stack","2.10.2",GL_INT,2, GL_MAX_PROJECTION_STACK_DEPTH },
    ValueContainer{ "SUBPIXEL_BITS","Number of bits of precision in x & y","3",GL_INT,4, GL_SUBPIXEL_BITS },
    ValueContainer{ "MAX_TEXTURE_SIZE","See the discussiion in Section 3.8","3.8",GL_INT,64, GL_MAX_TEXTURE_SIZE },
    ValueContainer{ "MAX_PIXEL_MAP_TABLE","Maximum size of a PixelMap translation table","3.6.2",GL_INT,32, GL_MAX_PIXEL_MAP_TABLE },
    ValueContainer{ "MAX_NAME_STACK_DEPTH","Maximum selection name stack depth","5.2",GL_INT,64, GL_MAX_NAME_STACK_DEPTH },
    ValueContainer{ "MAX_LIST_NESTING","Maximum display list call nesting","5.4",GL_INT,64, GL_MAX_LIST_NESTING },
    ValueContainer{ "MAX_EVAL_ORDER","Maximum evaluator polynomial order","5.1",GL_INT,8, GL_MAX_EVAL_ORDER },
    ValueContainer{ "MAX_ATTRIB_STACK_DEPTH","Maximum depth of the server attribute stack","6",GL_INT,16, GL_MAX_ATTRIB_STACK_DEPTH },
    ValueContainer{ "MAX_CLIENT_ATTRIB_STACK_DEPTH","Maximum depth of the client attribute stack","6",GL_INT,16, GL_MAX_CLIENT_ATTRIB_STACK_DEPTH },
    ValueContainer{ "AUX_BUFFERS","Number of auxiliary buffers","4.2.1",GL_INT,0, GL_AUX_BUFFERS },
};

std::vector<ValueContainer> implementationDependentValuesOptional = {
    ValueContainer{ "RGBA_MODE","True if color buffers store rgba","2.7",GL_BOOL,1, GL_RGBA_MODE },
    ValueContainer{ "INDEX_MODE","True if color buffers store indexes","2.7",GL_BOOL,1, GL_INDEX_MODE },
    ValueContainer{ "DOUBLEBUFFER","True if front & back buffer exists","4.2.1",GL_BOOL,1, GL_DOUBLEBUFFER },
    ValueContainer{ "STEREO","True if left & right buffers exist","6",GL_BOOL,1, GL_STEREO },
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