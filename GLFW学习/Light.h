#pragma once
#include<string>
class ShaderProgram;
struct DirLight
{
    std::string name;
	glm::vec3 direction= glm::vec3(0,1,0);
    glm::vec3 ambient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 diffuse = glm::vec3(0.6, 0.6, 0.6);
    glm::vec3 specular = glm::vec3(0.8, 0.8, 0.8);

    void Load(ShaderProgram* shaderProgram);
};

struct PointLight
{
    std::string name;

    glm::vec3 position;

    float constant=1;
    float linear=0.14;
    float quadratic=0.07;

    glm::vec3 ambient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 diffuse = glm::vec3(0.6, 0.6, 0.6);
    glm::vec3 specular = glm::vec3(0.8, 0.8, 0.8);
    void Load(ShaderProgram* shaderProgram);
};
