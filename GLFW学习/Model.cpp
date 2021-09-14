
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include"Camera.h"
#include"Mesh.h"
#include"LanGLTool.h"
#include"Shader.h"
#include"Window.h"
#include<string>
#include<vector>
using namespace std;
#include "Model.h"
void Model::Draw(ShaderProgram* shader)
{
    for (GLuint i = 0; i < this->meshes.size(); i++)
        this->meshes[i].Draw(shader);
}

void Model::loadModel(string path)
{
    //Assimp内置的导入器
    Assimp::Importer import;
    //读取文件，内部几何形状如果不是三角形就全转换为三角形，FlipUVs基于y轴翻转纹理坐标（不然可能会和想象的上下颠倒）
    //数据在scene中存储，子节点树存储数据的索引
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    //获取文件路径，稍后会尝试从路径中获得纹理等其他组件
    this->directory = path.substr(0, path.find_last_of("\\/"));

    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    //遍历所有当前节点的子网格
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        cout << "导入了【" << node->mName.C_Str() << "】节点的的第" << i << "个网格。" << endl;
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }
    // 递归处理该节点的子孙节点
    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        cout << "递归了【" << node->mName.C_Str() << "】节点的的第" << i << "个子节点。" << endl;
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    //一个网格包含顶点属性，顶点索引（存储该点是哪个顶点属性的下标），材质（漫反射/环境光纹理，镜面反射纹理）
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    //从平台无关的aiVector3D格式转换为我们自己的格式来用
    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        // 处理顶点坐标
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        //法线
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        //TODO: 目前只支持顶点单纹理坐标，第一个纹理坐标，Assimp允许一个模型的每个顶点有8个不同的纹理坐标。
        if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // 处理顶点索引
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        //face表示一个面，一个面根据我们的参数，总是三角形。
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // 处理材质，
    //
    if (mesh->mMaterialIndex >= 0)
    {
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            vector<Texture> diffuseMaps = this->loadMaterialTextures(material,
                aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            vector<Texture> specularMaps = this->loadMaterialTextures(material,
                aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }
    }

    return Mesh(vertices, indices, textures);
}
//将aiMaterial类型转换为纹理数组并注明类型
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    //获得该类型的纹理数量
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        //获取纹理名物理文件名
        mat->GetTexture(type, i, &str);
        Texture texture;
        string textureFilename(str.C_Str());
        string fileNameNoDir = textureFilename.substr(textureFilename.find_last_of("/\\") + 1);
        //cout << "找到的材质的" << typeName << "的物理文件名是"<< textureFilename << endl;
        //从路径下找到该文件
        texture.id = LanGLTool::CreateTexture(directory + '/' + fileNameNoDir);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}
