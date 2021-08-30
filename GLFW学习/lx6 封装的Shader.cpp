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
GLuint ShaderTest() {
    //������ɫ������
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 7) in vec3 position; // position����������λ��ֵΪ0
    layout (location = 8) in vec3 color; // position����������λ��ֵΪ0
    out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���
    void main()
    {
        gl_Position = vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
        vertexColor = vec4(color, 1.0f); 
    }
    )";
    GLuint vertexShader;
    //������ɫ�����󡣶�����ɫ��
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //����ɫ������Ϊĳ��Դ���롣ֻ��һ�����󡣲����ó���
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    //���ĳ����ɫ������ı���״̬
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec4 vertexColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
        out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
        void main()
        {
            color = vertexColor;
            //color=vec4(0.5f,0.5f,0.5f,0.5f);
        }
    )";
    GLuint fragmentShader;
    //����Ƭ����ɫ��
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    //������ɫ���������
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //�������и��ӵ���ɫ������Ϊ��ɫ������
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
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

    GLuint shaderProgram = ShaderTest();

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
        glUseProgram(shaderProgram);
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
