#version 330 core
layout (location = 0) in vec3 position; // position变量的属性位置值为0
layout (location = 1) in vec3 normal; // 顶点的法向量信息
layout (location = 2) in vec2 texCoord; // 顶点的法向量信息
out vec3 FragPos; // 顶点的世界位置
out vec3 Normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;
void main()
{
    TexCoord=texCoord;
    Normal=(model*vec4(normal,0)).xyz;
    gl_Position = projection*view*model*vec4(position, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    FragPos = vec3((model*vec4(position, 1.0))); 
}