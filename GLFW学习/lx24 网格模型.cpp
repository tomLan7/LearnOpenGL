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
#include"Shader.h"
#include"Window.h"
#include "Mesh.h"
#include"Model.h"
#include"LanGLTool.h"
#include"Light.h"
using namespace std;
using namespace glm;
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void changeState(glfwWindow* window);
bool keys[1024] = { 0 };
EulerFPSCamera* camera=new EulerFPSCamera();
mat4 lightModel;
vector<Vertex> vertices = {
    // positions          // normals           // texture coords
   {{ -0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 0.0f, 0.0f,} },
   {{  0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 1.0f, 0.0f,} },
   {{  0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 1.0f, 1.0f,} },
   {{  0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 1.0f, 1.0f,} },
   {{ -0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 0.0f, 1.0f,} },
   {{ -0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 0.0f, 0.0f,} },

   {{ -0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f,},  { 0.0f, 0.0f,} },
   {{  0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f,},  { 1.0f, 0.0f,} },
   {{  0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f,},  { 1.0f, 1.0f,} },
   {{  0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f,},  { 1.0f, 1.0f,} },
   {{ -0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f,},  { 0.0f, 1.0f,} },
   {{ -0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f,},  { 0.0f, 0.0f,} },

   {{ -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, { 1.0f, 0.0f,} },
   {{ -0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, { 1.0f, 1.0f,} },
   {{ -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, { 0.0f, 1.0f,} },
   {{ -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, { 0.0f, 1.0f,} },
   {{ -0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, { 0.0f, 0.0f,} },
   {{ -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, { 1.0f, 0.0f,} },

   {{  0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, { 1.0f, 0.0f,} },
   {{  0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, { 1.0f, 1.0f,} },
   {{  0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, { 0.0f, 1.0f,} },
   {{  0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, { 0.0f, 1.0f,} },
   {{  0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, { 0.0f, 0.0f,} },
   {{  0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, { 1.0f, 0.0f,} },

   {{ -0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, 1.0f,} },
   {{  0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, { 1.0f, 1.0f,} },
   {{  0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, { 1.0f, 0.0f,} },
   {{  0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, { 1.0f, 0.0f,} },
   {{ -0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, 0.0f,} },
   {{ -0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, 1.0f,} },

   {{ -0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, { 0.0f, 1.0f,} },
   {{  0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, { 1.0f, 1.0f,} },
   {{  0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, { 1.0f, 0.0f,} },
   {{  0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, { 1.0f, 0.0f,} },
   {{ -0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, { 0.0f, 0.0f,} },
   {{ -0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, { 0.0f, 1.0f } },
};
vector<GLuint> indexs = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
}; 
PointLight PLight{ "pointLights[0]",vec3(0,1,0) };
DirLight Dlight{ "dirLight",vec3(1,1,1),vec3(0.2,0.2,0.2),vec3(0.3,0.3,0.3), vec3(0.4,0.4,0.4), };

int main() {
    glfwWindow* window = glfwWindow::CreateWindow();
    //允许使用高级功能
    LanGLTool::initGLEW();
    //设置视口变换
    glViewport(0, 0, window->width, window->height);
    window->SetKeyCallback(key_callback2);

    window->SetWindowSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    window->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window->SetCursorPosCallback(mouse_callback);
    
    Mesh m2(vertices, indexs, vector<Texture>());
    //char str[] = "nanosuit/nanosuit.obj";
    char str[] = "X/dwarf.x";
    Model m(str);
    auto sp=ShaderProgram::CreateFromVertexAndFragmentPath("lx24.vert","lx24.frag");
    auto lightShaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx21.vert", "lx16light.frag");
    
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

        sp->Uniform("material.shininess",24);
        Dlight.Load(sp);
        PLight.Load(sp);
        sp->Uniform("viewPos",camera->pos);
        sp->Uniform("model",rotate(scale(mat4(1),vec3(0.1,0.1,0.1)),radians(90.f),vec3(1,0,0)));
        sp->Uniform("view", camera->ToViewMatrix());
        auto projection = glm::perspective(glm::radians(45.f), window->width / (float)window->height, 0.1f, 200.0f);
        sp->Uniform("projection", projection);

        m.Draw(sp);

        lightShaderProgram->User();
        lightModel = translate(mat4(1),PLight.position);
        lightShaderProgram->Uniform("scaleform", glm::scale(mat4(1), vec3(0.2)));
        lightShaderProgram->Uniform("transform", mat4(1));
        lightShaderProgram->Uniform("rotation", mat4(1));
        lightShaderProgram->Uniform("model", lightModel);
        lightShaderProgram->Uniform("view", camera->ToViewMatrix());
        lightShaderProgram->Uniform("projection", projection);

        m2.Draw(lightShaderProgram);

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
void changeState(glfwWindow* window) {
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
            case GLFW_KEY_LEFT:
            {
                vec4 newViewPos = translate(mat4(1), vec3(-0.1, 0, 0)) * camera->ToViewMatrix() * vec4(PLight.position, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                PLight.position = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_RIGHT:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0.1, 0, 0)) * camera->ToViewMatrix() * vec4(PLight.position, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                PLight.position = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_UP:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0, 0.1, 0)) * camera->ToViewMatrix() * vec4(PLight.position, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                PLight.position = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_DOWN:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0, -0.1, 0)) * camera->ToViewMatrix() * vec4(PLight.position, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                PLight.position = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
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
