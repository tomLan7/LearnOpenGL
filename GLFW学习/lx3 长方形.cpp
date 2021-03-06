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
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
GLuint indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};
void someOpenGLFunctionThatDrawsOurTriangle() {
    //使用线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //使用当前激活的着色器和之前的顶点属性配置和VBO的顶点数据(用VAO间接绑定)，
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

    //设置着色器代码
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 7) in vec3 position;
    void main()
    {
        gl_Position = vec4(position.x, position.y, position.z, 1.0);
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

        out vec4 color;

        void main()
        {
            color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
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
    //3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. 设置顶点属性指针
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(7);
    //5. 解绑VAO。状态已经存储进顶点数组中
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        //检查事件
        glfwPollEvents();
        glUseProgram(shaderProgram);
        glClearColor(0.2, 0.3f, 0.3f, 1.0f);
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
