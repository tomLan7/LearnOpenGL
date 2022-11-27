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

    int texWidth, texHeight;
    unsigned char* image = SOIL_load_image(FileName.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

}

bool lan::Texture::Load()
{
    return false;
}

void lan::Texture::Bind(GLenum TextureUnit)
{
}
