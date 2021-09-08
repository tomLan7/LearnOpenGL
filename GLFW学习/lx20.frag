#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec3 FragPos; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
in vec3 Normal;
uniform vec3 viewPos;

in vec3 VertexColor;
void main()
{ 
    // ������
    vec3 ambient = light.ambient * material.ambient;

    // �������
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // ����߹�
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);

    /*
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(LightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);//��������ⷽ����㷴��ⷽ��

    float spec = pow(max(dot(viewDir, reflectDir), 0.0),256);//?
    vec3 specular = specularStrength * spec * lightColor;

    vec3 ambient=ambientStrength*lightColor;
    vec3 result=(specular+ambient+diffuse)*objectColor;
    color = vec4(result,1);
    */
}