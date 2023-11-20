#pragma once
#include<string>
#include<memory>
#include<iostream>
#include <glm/glm.hpp>
#include"Matrix4F.h"
#include"GLObjectBase.h"
#include"light.h"

namespace lan {

	//代表一个着色器对象,
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

	//代表一个着色器程序,包含多个着色器对象
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
		//设置float类型变量
		bool  Uniform(const std::string& attrName, float Value) {
			GLint uniformIndex=glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex==-1) {
				rtn = false;
			}
			glUniform1f(uniformIndex, Value);
			return rtn;
		}
		//设置vec4类型变量
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

		bool Uniform(const std::string& attrName, Vector4F vec4) {
			return Uniform(attrName, vec4.x, vec4.y, vec4.z, vec4.w);
		}

		//设置vec4类型变量
		bool Uniform(const std::string& attrName, float ValueX, float ValueY, float ValueZ) {
			GLint uniformIndex = glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex == -1) {
				rtn = false;
			}
			else {
				glUniform3f(uniformIndex, ValueX, ValueY, ValueZ);
			}
			return rtn;
		}


		bool Uniform(const std::string& attrName, Vector3F vec3) {
			return Uniform(attrName, vec3.x, vec3.y, vec3.z);
		}

		bool Uniform(const std::string& attrName, DirectionalLight light) {
			bool ret =	Uniform(attrName + ".Color",light.Color);
			ret &=		Uniform(attrName + ".Direction", light.Direction);
			ret &=		Uniform(attrName + ".AmbientIntensity", light.AmbientIntensity);
			ret &=		Uniform(attrName + ".DiffuseIntensity", light.DiffuseIntensity);
			return ret;
		}

		//设置变量为某个纹理单元
		bool UniformTextureUnit(const std::string& attrName, int TextureUnitIndex) {
			GLint uniformIndex = glGetUniformLocation(this->ObjectId, attrName.c_str());
			bool rtn = true;
			if (uniformIndex == -1) {
				rtn = false;
			}
			else {
				glUniform1i(uniformIndex, TextureUnitIndex);
			}
			return rtn;
		}

		bool Uniform(const std::string& attrName, glm::vec3 value) {
			return Uniform(attrName, value.x, value.y, value.z);
		}

		bool Uniform(const std::string& attrName, glm::vec4 value) {
			return Uniform(attrName, value.x, value.y, value.z, value.w);

		}
		//设置变量为矩阵
		bool Uniform(const std::string& attName, const glm::mat4& mat);
		bool Uniform(const std::string& attName, const Matrix4F& mat);

		static ShaderProgram* Create() {
			return new ShaderProgram(glCreateProgram());
		}
		static ShaderProgram* CreateFromVertexAndFragmentPath(const std::string& vertexPath, const std::string& fragmentPath);
	};

}
