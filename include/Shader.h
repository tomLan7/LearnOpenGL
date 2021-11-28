#pragma once
#include<string>
#include<memory>
#include<iostream>
#include <glm/glm.hpp>
#include"Matrix4F.h"
/*封装原则：
* 一些经常用来分享的用智能指针包装。
* 一些经常临时使用的用栈区对象
* 一些需要长期保留的用堆区封装
*/
namespace lan {
	class OpenGLObjectBase {
	protected:
		GLuint ObjectId = 0;
		virtual ~OpenGLObjectBase() {
		}

		OpenGLObjectBase() = delete;
		OpenGLObjectBase(const OpenGLObjectBase&) = delete;

	public:
		OpenGLObjectBase(GLuint ObjectId) {
			this->ObjectId = ObjectId;
		}
		OpenGLObjectBase(OpenGLObjectBase&& other) {
			std::swap(this->ObjectId, other.ObjectId);
		}
		explicit operator GLuint() {
			return ObjectId;
		}
		GLboolean IsShader() {
			return glIsShader(ObjectId);
		}
		GLboolean IsProgram() {
			return glIsProgram(ObjectId);
		}
	};
	class Shader :public OpenGLObjectBase
	{
		GLenum ShaderType;
	public:
		Shader(GLuint ObjectId, GLenum Type) :OpenGLObjectBase(ObjectId) {
			ShaderType = Type;
		}

		Shader(GLenum Type) :Shader(glCreateShader(Type), Type) {
		}

		Shader(Shader&& other) :OpenGLObjectBase(std::move(other)) {
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
		std::shared_ptr<std::string> GetLog() {
			GLchar infoLog[512];
			glGetShaderInfoLog(ObjectId, 512, NULL, infoLog);
			return std::make_shared<std::string>(infoLog);
		}
	};
	class ShaderProgram :public OpenGLObjectBase {
	public:
		using OpenGLObjectBase::OpenGLObjectBase;

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

		std::shared_ptr<std::string> GetLog() {
			GLchar infoLog[512];
			glGetProgramInfoLog(ObjectId, 512, NULL, infoLog);
			return std::make_shared<std::string>(infoLog);
		}
		void User() {
			glUseProgram(ObjectId);
		}
		void  Uniform(const std::string& attrName, float Value) {
			glUniform1f(glGetUniformLocation(this->ObjectId, attrName.c_str()), Value);
		}
		void Uniform(const std::string& attrName, float ValueX, float ValueY, float ValueZ, float ValueW) {
			glUniform4f(glGetUniformLocation(this->ObjectId, attrName.c_str()), ValueX, ValueY, ValueZ, ValueW);
		}
		void UniformTextureIndex(const std::string& attName, int TextureIndex) {
			glUniform1i(glGetUniformLocation(this->ObjectId, attName.c_str()), TextureIndex);
		}
		void Uniform(const std::string& attName, glm::vec3 value) {
			glUniform3f(glGetUniformLocation(this->ObjectId, attName.c_str()), value.x, value.y, value.z);
		}
		void Uniform(const std::string& attName, glm::vec4 value) {
			glUniform4f(glGetUniformLocation(this->ObjectId, attName.c_str()), value.x, value.y, value.z, value.w);
		}
		void Uniform(const std::string& attName, const glm::mat4& mat);
		void Uniform(const std::string& attName, const Matrix4F& mat);

		static ShaderProgram* Create() {
			return new ShaderProgram(glCreateProgram());
		}
		static ShaderProgram* CreateFromVertexAndFragmentPath(const std::string& vertexPath, const std::string& fragmentPath);
	};

}
