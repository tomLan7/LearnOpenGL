// GLFWѧϰ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
GLFWwindow* initWindow() {
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
    return window;
}
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
    // λ��              // ��ɫ
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
};

void someOpenGLFunctionThatDrawsOurTriangle() {
    //ʹ���߿�ģʽ
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ʹ�õ�ǰ�������ɫ����֮ǰ�Ķ����������ú�VBO�Ķ�������(��VAO��Ӱ�)��
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//�ɶ�����ɫ�����ó��������� Ƭ����ɫ��
ShaderProgram* ShaderTest() {
    //������ɫ������
    auto shaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx7.vs", "lx7.frag");
    return shaderProgram;
}
void shaderTestMainLoop(ShaderProgram* shaderProgram) {
    // ����uniform��ɫ
    GLfloat timeValue = glfwGetTime();
    GLfloat offsetValue = (sin(timeValue) / 2) + 0.5;
    shaderProgram->Uniform("offset", offsetValue);
}
int main()
{
    GLFWwindow* window = initWindow();
    //����ʹ�ø߼�����
    initGLEW();

    int width, height;
    //��ô��ڻ�������С
    glfwGetFramebufferSize(window, &width, &height);
    //������ͼ�任
    glViewport(0, 0, width, height);

    GLuint VBO;
    //��������1��ʾ���ɻ�������������������Ժ������������ɶ�����󣬴�ʱVBOҲӦ���Ƕ�Ӧ��GLuint����ĵ�ַ����������������һ��ָ�롣
    glGenBuffers(1, &VBO);

    ShaderProgram* shaderProgram = ShaderTest();

    GLuint VAO;
    //����������������
    glGenVertexArrays(1, &VAO);

    GLuint EBO;
    glGenBuffers(1, &EBO);

    //�󶨶�������ΪĿ��
    glBindVertexArray(VAO);
    // 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ�� �ϱ��Ѿ����ù�
    //�����ͣ�һ������ֻ����һ��GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //���ݷ��͵��Կ��Ķ��㻺���С�ʵ���ϾͶ�Ӧ��VBO����������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 4. ���ö�������ָ��
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(7);
    //ƫ�Ƶ�λ���ֽ�Ϊ��λ
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(8);
    //5. ���VAO��״̬�Ѿ��洢������������
    glBindVertexArray(0);

    //��ѭ��
    while (!glfwWindowShouldClose(window))
    {
        //����¼�
        glfwPollEvents();
        shaderTestMainLoop(shaderProgram);
        shaderProgram->User();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        someOpenGLFunctionThatDrawsOurTriangle();
        glBindVertexArray(0);

        //������������˫�������
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
