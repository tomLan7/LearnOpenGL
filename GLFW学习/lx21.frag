#version 330 core
struct Material
{
    vec3 ambient;//基础颜色
    vec3 diffuse;//漫反射颜色
    vec3 specular;//镜面反射颜色
    float shininess;//镜面高光半径
};
uniform Material material;
struct Light
{
    vec3 position;
    vec3 ambient;//环境光强度
    vec3 diffuse;//漫反射强度
    vec3 specular;//镜面反射亮度强度
};
uniform Light light;

in vec3 FragPos; // 从顶点着色器传来的输入变量（名称相同、类型相同）
out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec4
in vec3 Normal;
uniform vec3 viewPos;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

in vec2 TexCoord;//插值后的纹理坐标
in vec3 VertexColor;
void main()
{
    // 环境光
    vec3 ambient = light.ambient * material.ambient;
    
    // 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // 镜面高光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular) * vec3(texture(ourTexture2,TexCoord));

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f)*texture(ourTexture1, TexCoord);
    
    ;
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