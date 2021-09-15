#pragma once
#include<vector>
class Model
{
public:
    /*  成员函数   */
    Model(GLchar* path)
    {
        this->loadModel(path);
    }
    Model(std::vector<Mesh>& all) {
        meshes = move(all);
    }
    void Draw(ShaderProgram* shader);
private:
    //已加载过的纹理，不会重新加载
    std::vector<Texture> textures_loaded;
    /*  模型数据  */
    std::vector<Mesh> meshes;
    std::string directory;

    /*  私有成员函数   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};