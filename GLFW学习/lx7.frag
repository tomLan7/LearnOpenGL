#version 330 core
in vec4 vertexColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
void main()
{
    color = vertexColor;
    //color=vec4(0.5f,0.5f,0.5f,0.5f);
}