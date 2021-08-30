
#include<iostream>
#include<fstream>
#include<sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
using namespace std;
inline ShaderProgram* ShaderProgram::CreateFromVertexAndFragmentPath(const std::string& vertexPath, const std::string& fragmentPath) {
	auto ShaderVertex = Shader::FromFile(vertexPath, GL_VERTEX_SHADER);
	auto ShaderFragment = Shader::FromFile(fragmentPath, GL_FRAGMENT_SHADER);
	if (!ShaderVertex.CompileShader()) {
		cout << ShaderVertex.GetLog() << endl;
		return nullptr;
	}
	if (!ShaderFragment.CompileShader()) {
		cout << ShaderFragment.GetLog() << endl;
		return nullptr;
	}
	auto shaderProgram = ShaderProgram::Create();
	shaderProgram->AttachShader(ShaderVertex);
	shaderProgram->AttachShader(ShaderFragment);
	if (!shaderProgram->LinkProgram()) {
		cout << ShaderFragment.GetLog() << endl;
		delete shaderProgram;
		return nullptr;
	}
	return shaderProgram;
}

Shader Shader::FromFile(const std::string& path, GLenum shaderType)
{
	std::string ShaderCode;
	std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// ���ļ�
		ShaderFile.open(path);
		std::stringstream ShaderStream;
		// ��ȡ�ļ��Ļ������ݵ�����
		ShaderStream << ShaderFile.rdbuf();
		// �ر��ļ�
		ShaderFile.close();
		// ת������GLchar����
		ShaderCode = ShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* ShaderCode_C = ShaderCode.c_str();
	Shader newShader(glCreateShader(shaderType));
	glShaderSource((GLuint)newShader, 1, &ShaderCode_C, NULL);
	return newShader;
}
