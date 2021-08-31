    #version 330 core
    layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
    layout (location = 1) in vec3 color; // position����������λ��ֵΪ0
    layout (location = 2) in vec2 texCoord; // ����
    out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���
    out vec2 TexCoord;
    uniform float offset;
    void main()
    {
        TexCoord=texCoord;
        gl_Position = vec4(position.x+offset,position.y,position.z, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
        vertexColor = vec4(color.x+offset,color.y+offset,color.z+offset,1.0); 
    }