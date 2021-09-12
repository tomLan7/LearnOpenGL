#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 normal; // ����ķ�������Ϣ
layout (location = 2) in vec2 texCoord; // ����ķ�������Ϣ
out vec3 FragPos; // ���������λ��
out vec3 Normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;
void main()
{
    TexCoord=texCoord;
    Normal=(model*vec4(normal,0)).xyz;
    gl_Position = projection*view*model*vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
    FragPos = vec3((model*vec4(position, 1.0))); 
}