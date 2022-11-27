
#include<SOIL/SOIL.h>
#include<string>
#include"GLDef.h"
namespace lan {
    class Texture
    {
    public:
        Texture(const std::string& FileName);

        bool Load();

        void Bind(GLenum TextureUnit);
    };
}
