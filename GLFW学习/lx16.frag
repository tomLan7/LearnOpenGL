#version 330 core
in vec4 vertexColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
in vec2 TexCoord;
void main()
{
    color = vertexColor;
}