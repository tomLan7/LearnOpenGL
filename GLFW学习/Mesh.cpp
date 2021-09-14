
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Camera.h"
#include"Shader.h"
#include"Window.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

void Mesh::Draw(ShaderProgram* shader)
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    //ÿ��
    for (GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // �ڰ�����ǰ��Ҫ�����ʵ�������Ԫ
                                          // �����������к� (N in diffuse_textureN)
        stringstream ss;
        string number;
        string name = this->textures[i].type;
        if (name == "texture_diffuse")
            ss << diffuseNr++; // ��GLuin���뵽string stream
        else if (name == "texture_specular")
            ss << specularNr++; // ��GLuin���뵽string stream
        number = ss.str();

        shader->UniformTextureIndex("material." + name + number, i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // ����Mesh
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
