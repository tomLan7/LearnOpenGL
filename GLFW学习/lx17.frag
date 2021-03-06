#version 330 core
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
uniform float ambientStrength;
uniform vec3 objectColor;
uniform vec3 lightColor;
void main()
{
    vec3 ambient=ambientStrength*lightColor;
    vec3 result=ambient*objectColor;
    color = vec4(result,1);
}