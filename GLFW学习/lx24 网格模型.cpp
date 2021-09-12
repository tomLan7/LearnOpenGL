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
GLuint CreateTexture(std::string textureName) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int texWidth, texHeight;
    unsigned char* image = SOIL_load_image(textureName.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    //GLuint textureid= SOIL_load_OGL_texture(textureName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //自动生成多级图像
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}
class Model
{
public:
    /*  成员函数   */
    Model(GLchar* path)
    {
        this->loadModel(path);
    }
    void Draw(ShaderProgram* shader);
private:
    /*  模型数据  */
    vector<Mesh> meshes;
    string directory;

    /*  私有成员函数   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
}; 
void initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(-1);
    }
}
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void changeState(Window* window);
bool keys[1024] = { 0 };
EulerFPSCamera* camera=new EulerFPSCamera();
int main() {
    Window* window = Window::CreateWindow();
    //允许使用高级功能
    initGLEW();

    //设置视口变换
    glViewport(0, 0, window->width, window->height);
    window->SetKeyCallback(key_callback2);
    window->SetWindowSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    window->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window->SetCursorPosCallback(mouse_callback);

    char str[] = "FBX 7_4 binary_Neck_Mech_Walker_by_3DHaupt/Neck_Mech_Walker_by_3DHaupt-(FBX 7.4 binary mit Animation).fbx";
    Model m(str);
    auto sp=ShaderProgram::CreateFromVertexAndFragmentPath("lx24.vert","lx24.frag");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    while (!window->IsShouldClose())
    {
        glfwPollEvents();
        window->SwapBuffers();
        changeState(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sp->User(); 

        sp->Uniform("dirLight.direciton", vec3(1, 1, 1));
        sp->Uniform("dirLight.ambient", vec3(1, 1, 1));
        sp->Uniform("dirLight.diffuse", vec3(1, 1, 1));
        sp->Uniform("dirLight.specular", vec3(1, 1, 1));

        sp->Uniform("model",rotate(mat4(1),radians(0.f),vec3(1,0,0)));
        sp->Uniform("view", camera->ToViewMatrix());
        auto projection = glm::perspective(glm::radians(45.f), window->width / (float)window->height, 0.1f, 200.0f);
        sp->Uniform("projection", projection);
        m.Draw(sp);
    }
    return 0;
}
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        keys[key] = true;
    }
    if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}
void changeState(Window* window) {
    for (int i = 0; i < 1024; i++) {
        if (keys[i] == true)
            switch (i)
            {
            case GLFW_KEY_ESCAPE:
                window->SetWindowShouldClose(GL_TRUE);
                break;
            case GLFW_KEY_W:
            case GLFW_KEY_A:
            case GLFW_KEY_S:
            case GLFW_KEY_D:
            case GLFW_KEY_Q:
            case GLFW_KEY_E:
            case GLFW_KEY_SPACE:
            case GLFW_KEY_LEFT_CONTROL:
            case GLFW_KEY_R:
            case GLFW_KEY_F:
                camera->keyOrder(i);
                break;
            /*case GLFW_KEY_LEFT:
            {
                vec4 newViewPos = translate(mat4(1), vec3(-0.1, 0, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_RIGHT:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0.1, 0, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_UP:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0, 0.1, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_DOWN:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0, -0.1, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }*/
            break;

            default:
                break;
            }
    }
}

double preX, preY;
bool start = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    if (start) {
        start = false;
        preX = xpos;
        preY = ypos;
        return;
    }
    double offsetX = xpos - preX;
    double offsetY = ypos - preY;
    camera->mouseOrder(offsetX, offsetY);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    preX = xpos;
    preY = ypos;
}
void Model::Draw(ShaderProgram* shader)
{
    for (GLuint i = 0; i < this->meshes.size(); i++)
        this->meshes[i].Draw(shader);
}

void Model::loadModel(string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));

    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }
    // 递归处理该节点的子孙节点
    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点坐标、法线和纹理坐标
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        //法线
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

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
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // 处理材质
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

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        system("chdir");
        texture.id = CreateTexture(directory+'/'+str.C_Str());
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);    
    }
    return textures;
}
