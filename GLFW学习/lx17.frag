#version 330 core
in vec4 vertexColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
uniform float ambientStrength;
uniform vec3 objectColor;
uniform vec3 lightColor;
void main()
{
    vec3 ambient=ambientStrength*lightColor;
    vec3 result=ambient*objectColor;
    color = vec4(result,1);
}