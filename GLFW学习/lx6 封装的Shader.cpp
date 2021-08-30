// GLFW学习.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>

GLFWwindow* initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //可以让用户手动修改窗口大小
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //退出并销毁资源
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
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

void someOpenGLFunctionThatDrawsOurTriangle() {
    //使用线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //使用当前激活的着色器和之前的顶点属性配置和VBO的顶点数据(用VAO间接绑定)，
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//由顶点着色器设置出参来控制 片段着色器
GLuint ShaderTest() {
    //设置着色器代码
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 7) in vec3 position; // position变量的属性位置值为0
    layout (location = 8) in vec3 color; // position变量的属性位置值为0
    out vec4 vertexColor; // 为片段着色器指定一个颜色输出
    void main()
    {
        gl_Position = vec4(position, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
        vertexColor = vec4(color, 1.0f); 
    }
    )";
    GLuint vertexShader;
    //创建着色器对象。定点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //绑定着色器对象为某个源代码。只绑定一个对象。不设置长度
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    //获得某个着色器对象的编译状态
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
        out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
        void main()
        {
            color = vertexColor;
            //color=vec4(0.5f,0.5f,0.5f,0.5f);
        }
    )";
    GLuint fragmentShader;
    //创建片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    //创建着色器程序对象
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //连接所有附加的着色器对象为着色器程序
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

int main()
{
    GLFWwindow* window = initWindow();
    //允许使用高级功能
    initGLEW();

    int width, height;
    //获得窗口缓冲区大小
    glfwGetFramebufferSize(window, &width, &height);
    //设置视图变换
    glViewport(0, 0, width, height);

    GLuint VBO;
    //缓冲区，1表示生成缓冲区对象的数量。可以函数调用中生成多个对象，此时VBO也应该是对应的GLuint数组的地址。缓冲区对象类似一个指针。
    glGenBuffers(1, &VBO);

    GLuint shaderProgram = ShaderTest();

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
    // 4. 设置顶点属性指针
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(7);
    //偏移单位以字节为单位
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(8);
    //5. 解绑VAO。状态已经存储进顶点数组中
    glBindVertexArray(0);

    //主循环
    while (!glfwWindowShouldClose(window))
    {
        //检查事件
        glfwPollEvents();
        glUseProgram(shaderProgram);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        someOpenGLFunctionThatDrawsOurTriangle();
        glBindVertexArray(0);

        //交换缓冲区，双缓冲机制
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
