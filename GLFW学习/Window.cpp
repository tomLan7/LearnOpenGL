
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include "Window.h"
#include<iostream>
using namespace std;
Window* Window::CreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //����ģʽ
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //�������û��ֶ��޸Ĵ��ڴ�С
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //�˳���������Դ
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    return new Window(window);
}
