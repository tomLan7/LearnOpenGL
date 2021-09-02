// GLFW学习.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include"Window.h"

using namespace std;
using namespace glm;
void initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(-1);
    }
}
GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
GLuint indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};
float Rotation=0;
float x, y,z;
float scale=1;
void someOpenGLFunctionThatDrawsOurTriangle(ShaderProgram* shaderProgram) {
    //使用线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    auto TransMat = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.0f));
    shaderProgram->Uniform("transform", TransMat);
    auto ScaleMat = glm::scale(glm::mat4(1), glm::vec3(::scale, ::scale, 1.f));
    shaderProgram->Uniform("scaleform", ScaleMat);
    auto RotationMat = glm::rotate(glm::mat4(1), radians(Rotation), glm::vec3(0.0, 0.0, 1.0));
    shaderProgram->Uniform("rotation", RotationMat);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    auto TransMat2 = glm::translate(glm::mat4(1), glm::vec3(x+0.2, y+0.2, 0.0f));
    shaderProgram->Uniform("transform", TransMat2);
    auto ScaleMat2 = glm::scale(glm::mat4(1), glm::vec3(1/::scale, 1/::scale, 1.f));
    shaderProgram->Uniform("scaleform", ScaleMat2);
    auto RotationMat2 = glm::rotate(glm::mat4(1), radians(-Rotation), glm::vec3(0.0, 0.0, 1.0));
    shaderProgram->Uniform("rotation", RotationMat2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES,0,3);
    //使用当前激活的着色器和之前的顶点属性配置和VBO的顶点数据(用VAO间接绑定)，
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void shaderTestMainLoop(ShaderProgram* shaderProgram) {
    // 更新uniform颜色
    GLfloat timeValue = glfwGetTime();
    GLfloat offsetValue = (sin(timeValue) / 2);
    shaderProgram->Uniform("offset", offsetValue);
    static GLfloat preTime = timeValue;
    std::cout << "经过了" << timeValue - preTime << "的时间" << std::endl;
    preTime=timeValue;
}
GLfloat mixValue = 0.2;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main()
{
    Window* window = Window::CreateWindow();
    //允许使用高级功能
    initGLEW();

    //设置视图变换
    glViewport(0, 0, window->width, window->height);
    window->SetKeyCallback(key_callback);



    GLuint VBO;
    //缓冲区，1表示生成缓冲区对象的数量。可以函数调用中生成多个对象，此时VBO也应该是对应的GLuint数组的地址。缓冲区对象类似一个指针。
    glGenBuffers(1, &VBO);

    ShaderProgram* shaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx11.vs", "lx11.frag");

    //纹理相关
    GLuint texture[2];
    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    int texWidth, texHeight;
    unsigned char* image = SOIL_load_image("container.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    unsigned char* image2 = SOIL_load_image("picture.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    //自动生成多级图像
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    SOIL_free_image_data(image2);




    GLuint VAO;
    //创建顶点数组数组
    glGenVertexArrays(1, &VAO);

    GLuint EBO;
    glGenBuffers(1, &EBO);

    //绑定顶点数组为目标
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用 上边已经调用过
    //绑定类型，一个窗口只能有一个GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //数据发送到显卡的顶点缓存中。实际上就对应了VBO缓冲区对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //偏移单位以字节为单位
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //偏移单位以字节为单位
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    //5. 解绑VAO。状态已经存储进顶点数组中
    glBindVertexArray(0);

    //主循环
    while (!window->IsShouldClose())
    {
        glfwWaitEventsTimeout(1/60.);
        //检查事件
        glfwPollEvents();
        shaderTestMainLoop(shaderProgram);
        shaderProgram->User();


        shaderProgram->Uniform("mixValue", mixValue);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        shaderProgram->Uniform("ourTexture1", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        shaderProgram->Uniform("ourTexture2", 1);

        glBindVertexArray(VAO);
        someOpenGLFunctionThatDrawsOurTriangle(shaderProgram);
        glBindVertexArray(0);

        //交换缓冲区，双缓冲机制
        window->SwapBuffers();
    }
    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }else
    // Change value of uniform with arrow keys (sets amount of textre mix)
    if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
    {
        mixValue += 0.1f;
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    else
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
    {
        mixValue -= 0.1f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
    else

    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        y +=0.1f;
    }
    else
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        y -= 0.1f;
    }
    else
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        x -= 0.1f;
    }
    else
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        x += 0.1f;
    }
    else
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        Rotation+=15;
    }
    else
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        Rotation -= 15;
    }
    else
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        ::scale*=1.1;
    }
    else
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        ::scale *=0.9;

    }

}