
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Light.h"
#include"Shader.h"

void DirLight::Load(ShaderProgram* shaderProgram)
{
	shaderProgram->Uniform(name+"."+"direction", direction);
	shaderProgram->Uniform(name + "." + "ambient", ambient);
	shaderProgram->Uniform(name + "." + "diffuse", diffuse);
	shaderProgram->Uniform(name + "." + "specular", specular);
}

//镜面反射亮度强度

void PointLight::Load(ShaderProgram* shaderProgram) {

	shaderProgram->Uniform(name + "." + "position", position);
	shaderProgram->Uniform(name + "." + "constant", constant);
	shaderProgram->Uniform(name + "." + "linear", linear);
	shaderProgram->Uniform(name + "." + "quadratic", quadratic);

	shaderProgram->Uniform(name + "." + "ambient", ambient);
	shaderProgram->Uniform(name + "." + "diffuse", diffuse);
	shaderProgram->Uniform(name + "." + "specular", specular);
}
