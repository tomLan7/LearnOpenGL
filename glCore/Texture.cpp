#include "Texture.h"
#include<iostream>
#include<SOIL/SOIL.h>
using namespace std;
/*不使用Magick库，调用Image时无法读取图片，未知错误
#include<Magick++.h>
#pragma comment(lib,"CORE_RL_Magick++_.lib")
#pragma comment(lib,"CORE_RL_MagickCore_.lib")
#pragma comment(lib,"CORE_RL_MagickWand_.lib")
Magick::Blob blob;
*/
#pragma comment(lib,"SOIL.lib")
lan::Texture::Texture(const std::string& FileName){

    glGenTextures(1, &obj);
    glBindTexture(GL_TEXTURE_2D, obj);
    int texWidth, texHeight;
    unsigned char* image = SOIL_load_image(FileName.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐进纹理
    SOIL_free_image_data(image);

    glTexParameterf(obj, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//更改纹理过滤方式为线性过滤
    glTexParameterf(obj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//更改纹理过滤方式为线性过滤

}

void lan::Texture::Bind(int UnitIndex)
{
    ActiveTexture(UnitIndex);//激活纹理单元，每个纹理单元有一组纹理对象（2D，3D等） 纹理单元数量有限，所以显卡内部的纹理数量有限，必须合图
    glBindTexture(GL_TEXTURE_2D, obj);
}

int lan::Texture::ActiveTexture(int index)
{
    if (index > 0 && index < GetMaxCombinedTextureImageUnitsCount()) {
        glActiveTexture(GL_TEXTURE0 + index);
    }
    else {
        throw new exception("尝试激活纹理单元超出允许数量");
    }
}

constexpr int lan::Texture::GetMaxCombinedTextureImageUnitsCount()
{
    return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
}
