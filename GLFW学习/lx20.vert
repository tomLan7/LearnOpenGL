#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 normal; // ����ķ�������Ϣ
out vec3 FragPos; // ���������λ��
out vec3 Normal;
uniform mat4 transform;
uniform mat4 scaleform;
uniform mat4 rotation;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
out vec3 VertexColor;//��ʹ��
void main()
{
    Normal=(model*rotation*vec4(normal,0)).xyz;
    gl_Position = projection*view*model*transform*rotation*scaleform*vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
    FragPos = vec3((model*transform*rotation*scaleform*vec4(position, 1.0)).xyz); 
}