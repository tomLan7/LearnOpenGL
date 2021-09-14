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


void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void changeState(Window* window);
bool keys[1024] = { 0 };
EulerFPSCamera* camera=new EulerFPSCamera();
vec3 lightPos(5, 1, 1);
mat4 lightModel;
float vertices[] = {
    // positions                  // texture coords
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, 1.0f
};

int main() {
    Window* window = Window::CreateWindow();
    //允许使用高级功能
    LanGLTool::initGLEW();
    Mesh m(,,);
    //设置视口变换
    glViewport(0, 0, window->width, window->height);
    window->SetKeyCallback(key_callback2);
    window->SetWindowSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    window->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window->SetCursorPosCallback(mouse_callback);

    char str[] = "nanosuit/nanosuit.obj";
    Model m(str);
    auto sp=ShaderProgram::CreateFromVertexAndFragmentPath("lx24.vert","lx24.frag");
    auto lightShaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx24.vert", "lx21.frag");
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

        sp->Uniform("model",rotate(mat4(1),radians(90.f),vec3(1,0,0)));
        sp->Uniform("view", camera->ToViewMatrix());
        auto projection = glm::perspective(glm::radians(45.f), window->width / (float)window->height, 0.1f, 200.0f);
        sp->Uniform("projection", projection);

        m.Draw(sp);

        glBindVertexArray(0);
        lightModel = translate(mat4(1), lightPos);
        lightShaderProgram->Uniform("model", lightModel);
        lightShaderProgram->Uniform("scaleform", glm::scale(mat4(1), vec3(1)));

        glDrawArrays(GL_TRIANGLES, 0, 36);


        glBindVertexArray(0);
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
