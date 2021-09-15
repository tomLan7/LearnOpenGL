#version 330 core
struct Material
{
    sampler2D texture_diffuse1;//纹理颜色就是漫反射颜色和基础颜色
    sampler2D texture_specular1;
    float shininess;//镜面高光半径
};
uniform Material material;
struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir); 

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;//环境光强度
    vec3 diffuse;//漫反射强度
    vec3 specular;//镜面反射亮度强度
};
#define NR_POINT_LIGHTS 1  
uniform PointLight pointLights[NR_POINT_LIGHTS];
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;//切光角余弦
    float outerCutOff;//切光角余弦

    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;//环境光强度
    vec3 diffuse;//漫反射强度
    vec3 specular;//镜面反射亮度强度
};
uniform SpotLight spotLight;
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

in vec3 FragPos; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec3 Normal;
uniform vec3 viewPos;



in vec2 TexCoord;//插值后的纹理坐标
void main()
{

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 第一步，计算平行光照
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // 第二步，计算顶点光照
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    
    // 第三部，计算 Spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    color=vec4(result,1);
    //color = vec4(vec3(texture(material.texture_diffuse1, TexCoord)),1);
    //Spotlight();
    
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射强度
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并各个光照分量
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));
   
    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 计算衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 将各个分量合并
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
        //距离衰减
        vec3 FragDir=normalize(fragPos-light.position);
        float distance = length(FragDir);
        float attenuation = 1.0f / (light.constant + light.linear*distance +light.quadratic*(distance*distance));
        //环境光
        vec3 ambient = light.ambient * vec3(texture(material.texture_specular1, TexCoord));
         // 漫反射光
        vec3 norm = normalize(Normal);
        
        float diff = max(dot(norm, -FragDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_specular1, TexCoord));
    
        // 镜面高光
        vec3 reflectDir = reflect(-FragDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1,TexCoord));

    vec3 lightDir = normalize(light.direction);
    float theta=dot(lightDir,FragDir);
    float epsilon=light.cutOff-light.outerCutOff;
    float intensity=clamp((theta-light.outerCutOff)/epsilon,0.0,1.0);

    vec3 result = (ambient + diffuse + specular)*intensity*attenuation;//光线强度
   return result;
}