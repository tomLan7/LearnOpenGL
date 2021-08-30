
#include<iostream>
#include<fstream>
#include<sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
using namespace std;
ShaderProgram* ShaderProgram::CreateFromVertexAndFragmentPath(const std::string& vertexPath, const std::string& fragmentPath) {
	auto ShaderVertex = Shader::FromFile(vertexPath, GL_VERTEX_SHADER);
	auto ShaderFragment = Shader::FromFile(fragmentPath, GL_FRAGMENT_SHADER);
	if (!ShaderVertex.CompileShader()) {
		cout << "Failed To Shader Compile"<<ShaderVertex.GetLog() << endl;
		return nullptr;
	}
	if (!ShaderFragment.CompileShader()) {
		cout << "Failed To Shader Compile" << ShaderFragment.GetLog() << endl;
		return nullptr;
	}
	auto shaderProgram = ShaderProgram::Create();
	shaderProgram->AttachShader(ShaderVertex);
	shaderProgram->AttachShader(ShaderFragment);
	if (!shaderProgram->LinkProgram()) {
		cout << "Failed To Shader Link" << shaderProgram->GetLog() << endl;
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
		// 打开文件
		ShaderFile.open(path);
		std::stringstream ShaderStream;
		// 读取文件的缓冲内容到流中
		ShaderStream << ShaderFile.rdbuf();
		// 关闭文件
		ShaderFile.close();
		// 转换流至GLchar数组
		ShaderCode = ShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* ShaderCode_C = ShaderCode.c_str();
	Shader newShader(glCreateShader(shaderType), shaderType);

	glShaderSource((GLuint)newShader, 1, &ShaderCode_C, NULL);
	return newShader;
}
