#version 330 core
struct Material
{
    sampler2D diffuse;//纹理颜色就是漫反射颜色和基础颜色
    sampler2D specular;
    float shininess;//镜面高光半径
};
uniform Material material;
struct Light
{
    vec4 position;
    vec3 ambient;//环境光强度
    vec3 diffuse;//漫反射强度
    vec3 specular;//镜面反射亮度强度
    
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

in vec3 FragPos; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec3 Normal;
uniform vec3 viewPos;
uniform vec3 viewDirection;
uniform float cutOff;//切光角余弦
uniform float outerCutOff;//外切光角余弦

uniform sampler2D ourTexture2;

in vec2 TexCoord;//插值后的纹理坐标
in vec3 VertexColor;
void DirectionalLightAndPointLight(){

    //距离衰减
    float distance = length(light.position.xyz - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear*distance +light.quadratic*(distance*distance));

    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir;
    if(light.position.w==0){//根据w判断是定向光还是点光源
        lightDir=normalize(-(light.position.xyz));
    }else{
        lightDir=normalize(light.position.xyz - FragPos);
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    // 镜面高光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));


    //合成最终光照效果
    vec3 result = ambient + diffuse + specular;//光线强度
    color = vec4(result*attenuation, 1.0f);
}
void Spotlight(){
    vec3 lightDir=normalize(viewDirection);
    vec3 FragDir = normalize(FragPos-viewPos);
    
    
    if(dot(lightDir,FragDir)>=cutOff){
        //距离衰减
        float distance = length(viewPos - FragPos);
        float attenuation = 1.0f / (light.constant + light.linear*distance +light.quadratic*(distance*distance));

        //漫反射
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, -lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

        //镜面反射
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(-viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));
    

         
        vec3 result =  (diffuse + specular)*attenuation;//光线强度
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
    vec3 reflectDir = reflect(-lightDir, norm);//根据入射光方向计算反射光方向

    float spec = pow(max(dot(viewDir, reflectDir), 0.0),256);//?
    vec3 specular = specularStrength * spec * lightColor;

    vec3 ambient=ambientStrength*lightColor;
    vec3 result=(specular+ambient+diffuse)*objectColor;
    color = vec4(result,1);
    */
}