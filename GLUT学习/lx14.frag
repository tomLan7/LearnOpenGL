#version 330

in vec2 TexCoord0;
in vec3 Normal0;

out vec4 FragColor;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
};
uniform DirectionalLight gDirectionalLight;
uniform sampler2D gSampler;

void main()
{
    vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);
    vec4 DiffuseColor;
    
    vec3 norm = normalize(Normal0);
    vec3 lightDir = -normalize(gDirectionalLight.Direction);
    float DiffuseFactor = max(dot(norm, lightDir), 0.0);
    DiffuseColor=vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor,1);

    FragColor = texture2D(gSampler, TexCoord0.xy) * (AmbientColor + DiffuseColor);
};