#version 330 core
in vec4 vertexColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
in vec2 TexCoord;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixValue;
void main()
{
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x,1-TexCoord.y)),mixValue);
}