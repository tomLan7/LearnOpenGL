#pragma once
#include<string>
#include<memory>
/*封装原则：
* 一些经常用来分享的用智能指针包装。
* 一些经常临时使用的用栈区对象
* 一些需要长期保留的用堆区封装
*/
class OpenGLObjectBase {
protected:
	GLuint ObjectId;
	virtual ~OpenGLObjectBase() {
		glDeleteShader(ObjectId);
	}
	OpenGLObjectBase(GLuint ObjectId) {
		this->ObjectId = ObjectId;
	}
public:
	explicit operator GLuint() {
		return ObjectId;
	}
};
class Shader:public OpenGLObjectBase
{
	GLenum ShaderType;
public:
	Shader(GLuint ObjectId, GLenum Type):OpenGLObjectBase (ObjectId){
		ShaderType = Type;
	}
	Shader(GLenum Type) :OpenGLObjectBase(glCreateShader(Type)) {
		ShaderType = Type;
	}

	static Shader FromFile(const std::string& path, GLenum shaderType);
	GLint CompileShader() {
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
class ShaderProgram:public OpenGLObjectBase {
public:
	using OpenGLObjectBase::OpenGLObjectBase;
	
	void AttachShader(Shader& shader) {
		glAttachShader(ObjectId,(GLuint)shader);
	}
	GLint LinkProgram() {
		glLinkProgram(ObjectId);
		GLint success;
		glGetShaderiv(ObjectId, GL_LINK_STATUS, &success);
		return success;
	}
	std::shared_ptr<std::string> GetLog() {
		GLchar infoLog[512];
		glGetProgramInfoLog(ObjectId, 512, NULL, infoLog);
		return std::make_shared<std::string>(infoLog);
	}
	void User() {
		glUseProgram(ObjectId);
	}

	static ShaderProgram* Create() {
		return new ShaderProgram(glCreateProgram());
	}
	static ShaderProgram* CreateFromVertexAndFragmentPath(const std::string& vertexPath, const std::string& fragmentPath);
};
