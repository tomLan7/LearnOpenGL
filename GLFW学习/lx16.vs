#version 330 core
layout (location = 0) in vec3 position; // position变量的属性位置值为0
layout (location = 1) in vec3 color; // position变量的属性位置值为0
out vec4 vertexColor; // 为片段着色器指定一个颜色输出
uniform mat4 transform;
uniform mat4 scaleform;
uniform mat4 rotation;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    gl_Position = projection*view*model*transform*rotation*scaleform*vec4(position, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    //gl_Position = projection*view*model*vec4(position, 1.0);
    vertexColor = vec4(lightColor * objectColor,1.0); 
}