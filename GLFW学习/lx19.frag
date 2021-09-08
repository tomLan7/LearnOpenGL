#version 330 core
in vec3 FragPos; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec3 Normal;
in vec3 LightPos;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform float specularStrength;
uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 VertexColor;
void main()
{
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(LightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);//根据入射光方向计算反射光方向

    float spec = pow(max(dot(viewDir, reflectDir), 0.0),256);//
    vec3 specular = specularStrength * spec * lightColor;

    vec3 ambient=ambientStrength*lightColor;
    vec3 result=(specular+ambient+diffuse)*objectColor;
    color = vec4(result,1);
}