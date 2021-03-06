#version 330 core
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
    color = texture(ourTexture, TexCoord)*vertexColor;
    //color = vertexColor;
    //color=vec4(0.5f,0.5f,0.5f,0.5f);
}