
#define GLEW_STATIC
#include <GL/glew.h>
#include "ArrayBufferTarget.h"
namespace lan {
    GLBuffer* ArrayBufferTarget::current_buffer=nullptr;
}