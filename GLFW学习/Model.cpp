
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
    //Assimp���õĵ�����
    Assimp::Importer import;
    //��ȡ�ļ����ڲ�������״������������ξ�ȫת��Ϊ�����Σ�FlipUVs����y�ᷭת�������꣨��Ȼ���ܻ����������µߵ���
    //������scene�д洢���ӽڵ����洢���ݵ�����
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    //��ȡ�ļ�·�����Ժ�᳢�Դ�·���л��������������
    this->directory = path.substr(0, path.find_last_of("\\/"));

    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    //�������е�ǰ�ڵ��������
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        cout << "�����ˡ�" << node->mName.C_Str() << "���ڵ�ĵĵ�" << i << "������" << endl;
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }
    // �ݹ鴦��ýڵ������ڵ�
    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        cout << "�ݹ��ˡ�" << node->mName.C_Str() << "���ڵ�ĵĵ�" << i << "���ӽڵ㡣" << endl;
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    //һ����������������ԣ������������洢�õ����ĸ��������Ե��±꣩�����ʣ�������/�������������淴������
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    //��ƽ̨�޹ص�aiVector3D��ʽת��Ϊ�����Լ��ĸ�ʽ����
    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        // ����������
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        //����
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        //TODO: Ŀǰֻ֧�ֶ��㵥�������꣬��һ���������꣬Assimp����һ��ģ�͵�ÿ��������8����ͬ���������ꡣ
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
    // ����������
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        //face��ʾһ���棬һ����������ǵĲ��������������Ρ�
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // ������ʣ�
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
//��aiMaterial����ת��Ϊ�������鲢ע������
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    //��ø����͵���������
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        //��ȡ�����������ļ���
        mat->GetTexture(type, i, &str);
        Texture texture;
        string textureFilename(str.C_Str());
        string fileNameNoDir = textureFilename.substr(textureFilename.find_last_of("/\\") + 1);
        //cout << "�ҵ��Ĳ��ʵ�" << typeName << "�������ļ�����"<< textureFilename << endl;
        //��·�����ҵ����ļ�
        texture.id = LanGLTool::CreateTexture(directory + '/' + fileNameNoDir);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}
