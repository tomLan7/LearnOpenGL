#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 color; // position����������λ��ֵΪ0
out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���
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
    gl_Position = projection*view*model*transform*rotation*scaleform*vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
    //gl_Position = projection*view*model*vec4(position, 1.0);
    vertexColor = vec4(lightColor * objectColor,1.0); 
}