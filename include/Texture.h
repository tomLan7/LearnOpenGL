
#include<SOIL/SOIL.h>
#include<string>
#include"GLDef.h"
namespace lan {
    class Texture
    {
        GLuint obj;
    public:
        Texture(const std::string& FileName);

        void Bind(int UnitIndex);
        virtual ~Texture() {
            glDeleteTextures(1, &obj);
        }


        static int ActiveTexture(int index=0);

        //可用的纹理单元数量
        static int GetMaxCombinedTextureImageUnitsCount();

    };
}
