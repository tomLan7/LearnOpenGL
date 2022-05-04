#pragma once
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


}
