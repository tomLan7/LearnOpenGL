    #version 330 core
    layout (location = 7) in vec3 position; // position变量的属性位置值为0
    layout (location = 8) in vec3 color; // position变量的属性位置值为0
    out vec4 vertexColor; // 为片段着色器指定一个颜色输出
    void main()
    {
        gl_Position = vec4(position, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
        vertexColor = vec4(color, 1.0f); 
    }