    #version 330 core
    layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
    layout (location = 1) in vec3 color; // position����������λ��ֵΪ0
    layout (location = 2) in vec2 texCoord; // ����
    out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���
    out vec2 TexCoord;
    uniform float offset;
    uniform mat4 transform;
    uniform mat4 scaleform;
    uniform mat4 rotation;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        TexCoord=texCoord;
        gl_Position = projection*view*model*transform*rotation*scaleform*vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
        //gl_Position = projection*view*model*vec4(position, 1.0);
        vertexColor = vec4(color.x+offset,color.y+offset,color.z+offset,1.0); 
    }