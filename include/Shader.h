#pragma once
#include<string>
#include<memory>
#include<iostream>
#include <glm/glm.hpp>
#include"Matrix4F.h"
#include"GLObjectBase.h"

namespace lan {
	
	class Shader :public GLObjectBase
	{
		GLenum ShaderType;
	public:
		Shader(GLuint ObjectId, GLenum Type) :GLObjectBase(ObjectId) {
			ShaderType = Type;
		}

		Shader(GLenum Type) :Shader(glCreateShader(Type), Type) {
		}

		Shader(Shader&& other) :GLObjectBase(std::move(other)) {
			std::swap(this->ShaderType, other.ShaderType);
		}

		~Shader() {
			glDeleteShader(ObjectId);
		}

		void ShaderSource(const std::string& source) {
			const GLchar* str = source.c_str();
			glShaderSource(ObjectId, 1, &str, 0);
		}

		static Shader FromFile(const std::string& path, GLenum shaderType);

		GLboolean CompileShader() {
			glCompileShader(ObjectId);
			GLint success;
			glGetShaderiv(ObjectId, GL_COMPILE_STATUS, &success);
			return success;
		}
		std::string GetLog() {
			GLchar infoLog[512];
			glGetShaderInfoLog(ObjectId, 512, NULL, infoLog);
			return infoLog;
		}
	};

	class ShaderProgram :public GLObjectBase {
	public:
		using GLObjectBase::GLObjectBase;

		void AttachShader(Shader& shader) {
			glAttachShader(ObjectId, (GLuint)shader);
		}
		void DetachShader(Shader& shader) {
			glDetachShader(ObjectId, (GLuint)shader);
		}
		~ShaderProgram() {
			glDeleteProgram(ObjectId);
		}
		GLboolean LinkProgram() {
			glLinkProgram(ObjectId);
			GLint success;
			glGetShaderiv(ObjectId, GL_LINK_STATUS, &success);
			return success;
		}
		void ValidateProgram() {
			glValidateProgram(ObjectId);
		}
		GLint GetAttribLocation(std::string str) {
			return glGetAttribLocation(ObjectId,str.c_str());
		}

		std::string GetLog() {
			GLchar infoLog[512];
			glGetProgramInfoLog(ObjectId, 512, NULL, infoLog);
			return infoLog;
		}
		void User() {
			glUseProgram(ObjectId);
		}
		bool  Uniform(const std::string& attrName, float Value) {
			GLint uniformIndex=glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex==-1) {
				rtn = false;
			}
			glUniform1f(uniformIndex, Value);
			return rtn;
		}
		bool Uniform(const std::string& attrName, float ValueX, float ValueY, float ValueZ, float ValueW) {
			GLint uniformIndex = glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex == -1) {
				rtn = false;
			}
			else {
				glUniform4f(uniformIndex, ValueX, ValueY, ValueZ, ValueW);
			}
			return rtn;
		}
		bool UniformTextureIndex(const std::string& attrName, int TextureIndex) {
			GLint uniformIndex = glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex == -1) {
				rtn = false;
			}
			else {
				glUniform1i(uniformIndex, TextureIndex);
			}
			return rtn;
		}
		bool Uniform(const std::string& attrName, glm::vec3 value) {
			GLint uniformIndex = glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex == -1) {
				rtn = false;
			}
			else {
				glUniform3f(uniformIndex, value.x, value.y, value.z);
			}
			return rtn;
		}
		bool Uniform(const std::string& attrName, glm::vec4 value) {
			GLint uniformIndex = glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex == -1) {
				rtn = false;
			}
			else {
				glUniform4f(uniformIndex, value.x, value.y, value.z, value.w);
			}
			return rtn;
			
		}
		bool Uniform(const std::string& attName, const glm::mat4& mat);
		bool Uniform(const std::string& attName, const Matrix4F& mat);

		static ShaderProgram* Create() {
			return new ShaderProgram(glCreateProgram());
		}
		static ShaderProgram* CreateFromVertexAndFragmentPath(const std::string& vertexPath, const std::string& fragmentPath);
	};

}
