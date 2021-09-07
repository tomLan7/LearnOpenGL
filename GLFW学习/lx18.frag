#version 330 core
in vec3 FragPos; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec3 Normal;
in vec3 LightPos;
uniform float ambientStrength;
uniform vec3 objectColor;
uniform vec3 lightColor;
void main()
{
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(LightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambient=ambientStrength*lightColor;
    vec3 result=(ambient+diffuse)*objectColor;
    color = vec4(result,1);
}