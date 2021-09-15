#pragma once
#include<vector>
class Model
{
public:
    /*  ��Ա����   */
    Model(GLchar* path)
    {
        this->loadModel(path);
    }
    Model(std::vector<Mesh>& all) {
        meshes = move(all);
    }
    void Draw(ShaderProgram* shader);
private:
    //�Ѽ��ع��������������¼���
    std::vector<Texture> textures_loaded;
    /*  ģ������  */
    std::vector<Mesh> meshes;
    std::string directory;

    /*  ˽�г�Ա����   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};