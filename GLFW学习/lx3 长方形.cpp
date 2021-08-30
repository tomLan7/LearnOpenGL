// GLFWѧϰ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>

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
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
void someOpenGLFunctionThatDrawsOurTriangle() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    void main()
    {
        gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
    )";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    const char* fragmentShaderSource = R"(
        #version 330 core

        out vec4 color;

        void main()
        {
            color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //4. ���VAO
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        //����¼�
        glfwPollEvents();
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        someOpenGLFunctionThatDrawsOurTriangle();
        glBindVertexArray(0);

        //������������˫�������
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
