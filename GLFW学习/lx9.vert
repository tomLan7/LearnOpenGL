    #version 330 core
    layout (location = 0) in vec3 position; // position变量的属性位置值为0
    layout (location = 1) in vec3 color; // position变量的属性位置值为0
    layout (location = 2) in vec2 texCoord; // 纹理
    out vec4 vertexColor; // 为片段着色器指定一个颜色输出
    out vec2 TexCoord;
    uniform float offset;
    void main()
    {
        TexCoord=texCoord;
        gl_Position = vec4(position.x+offset,position.y,position.z, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
        vertexColor = vec4(color.x+offset,color.y+offset,color.z+offset,1.0); 
    }