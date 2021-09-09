#version 330 core
struct Material
{
    sampler2D diffuse;//������ɫ������������ɫ�ͻ�����ɫ
    sampler2D specular;
    float shininess;//����߹�뾶
};
uniform Material material;
struct Light
{
    vec4 position;
    vec3 ambient;//������ǿ��
    vec3 diffuse;//������ǿ��
    vec3 specular;//���淴������ǿ��
    
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

in vec3 FragPos; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
in vec3 Normal;
uniform vec3 viewPos;
uniform vec3 viewDirection;
uniform float cutOff;//�й������
uniform float outerCutOff;//���й������

uniform sampler2D ourTexture2;

in vec2 TexCoord;//��ֵ�����������
in vec3 VertexColor;
void DirectionalLightAndPointLight(){

    //����˥��
    float distance = length(light.position.xyz - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear*distance +light.quadratic*(distance*distance));

    // ������
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // �������
    vec3 norm = normalize(Normal);
    vec3 lightDir;
    if(light.position.w==0){//����w�ж��Ƕ���⻹�ǵ��Դ
        lightDir=normalize(-(light.position.xyz));
    }else{
        lightDir=normalize(light.position.xyz - FragPos);
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    // ����߹�
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));


    //�ϳ����չ���Ч��
    vec3 result = ambient + diffuse + specular;//����ǿ��
    color = vec4(result*attenuation, 1.0f);
}
void Spotlight(){
    vec3 lightDir=normalize(viewDirection);
    vec3 FragDir = normalize(FragPos-viewPos);
    
    
    if(dot(lightDir,FragDir)>=cutOff){
        //����˥��
        float distance = length(viewPos - FragPos);
        float attenuation = 1.0f / (light.constant + light.linear*distance +light.quadratic*(distance*distance));

        //������
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, -lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

        //���淴��
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(-viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));
    

         
        vec3 result =  (diffuse + specular)*attenuation;//����ǿ��
        color=vec4(result,1);
        }else{
    }
}
void main()
{

    Spotlight();
    //Spotlight();
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