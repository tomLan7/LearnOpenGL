
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include "GLFWWindow.h"
#include<iostream>
using namespace std;
glfwWindow* glfwWindow::CreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //可以让用户手动修改窗口大小
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //退出并销毁资源
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    return new glfwWindow(window);
}
