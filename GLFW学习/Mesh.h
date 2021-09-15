#pragma once
#include <iostream>
#include<string>
#include<vector>
#include <sstream>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
struct Texture
{
    GLuint id;
    std::string type;
    aiString path;
};
class ShaderProgram;
class Mesh
{
public:
    //顶点属性
    std::vector<Vertex> vertices;
    //使用的顶点索引
    std::vector<GLuint> indices;
    //纹理坐标
    std::vector<Texture> textures;
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const std::vector<Texture>& textures)
    {
        this->vertices = std::move(vertices);
        this->indices = std::move(indices);
        this->textures = textures;

        this->setupMesh();
    }
    void Draw(ShaderProgram* shader);

private:
    GLuint VAO, VBO, EBO;
    void setupMesh()
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
            &this->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
            &this->indices[0], GL_STATIC_DRAW);

        // 设置顶点坐标指针
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (GLvoid*)0);
        // 设置法线指针
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, Normal));
        // 设置顶点的纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};