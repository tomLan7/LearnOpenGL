#version 330 core
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec2 TexCoord;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixValue;
void main()
{
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x,1-TexCoord.y)),mixValue);
}