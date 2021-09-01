// GLFWѧϰ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL/SOIL.h>
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
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};
GLuint indices[] = { // ע��������0��ʼ! 
    0, 1, 3, // ��һ��������
    1, 2, 3  // �ڶ���������
};
void someOpenGLFunctionThatDrawsOurTriangle() {
    //ʹ���߿�ģʽ
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES,0,3);
    //ʹ�õ�ǰ�������ɫ����֮ǰ�Ķ����������ú�VBO�Ķ�������(��VAO��Ӱ�)��
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//�ɶ�����ɫ�����ó��������� Ƭ����ɫ��
ShaderProgram* ShaderTest() {
    //������ɫ������
    auto shaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx9.vs", "lx9.frag");
    return shaderProgram;
}
void shaderTestMainLoop(ShaderProgram* shaderProgram) {
    // ����uniform��ɫ
    GLfloat timeValue = glfwGetTime();
    GLfloat offsetValue = (sin(timeValue) / 2);
    shaderProgram->Uniform("offset", offsetValue);
    static GLfloat preTime = timeValue;
    std::cout << "������" << timeValue - preTime << "��ʱ��" << std::endl;
    preTime=timeValue;
}
GLfloat mixValue = 0.2;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
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
    glfwSetKeyCallback(window, key_callback);



    GLuint VBO;
    //��������1��ʾ���ɻ�������������������Ժ������������ɶ�����󣬴�ʱVBOҲӦ���Ƕ�Ӧ��GLuint����ĵ�ַ����������������һ��ָ�롣
    glGenBuffers(1, &VBO);

    ShaderProgram* shaderProgram = ShaderTest();

    //�������
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
    //�Զ����ɶ༶ͼ��
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    SOIL_free_image_data(image2);




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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //ƫ�Ƶ�λ���ֽ�Ϊ��λ
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //ƫ�Ƶ�λ���ֽ�Ϊ��λ
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    //5. ���VAO��״̬�Ѿ��洢������������
    glBindVertexArray(0);

    //��ѭ��
    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEventsTimeout(1/60.);
        //����¼�
        glfwPollEvents();
        shaderTestMainLoop(shaderProgram);
        shaderProgram->User();


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        shaderProgram->Uniform("ourTexture1", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        shaderProgram->Uniform("ourTexture2", 1);

        shaderProgram->Uniform("mixValue", mixValue);
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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    // Change value of uniform with arrow keys (sets amount of textre mix)
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        mixValue += 0.1f;
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        mixValue -= 0.1f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
}