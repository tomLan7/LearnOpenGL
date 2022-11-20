#pragma once
namespace lan {
	class GLObjectBase {
	protected:
		GLuint ObjectId = 0;
		virtual ~GLObjectBase() {
		}

		GLObjectBase() = delete;
		GLObjectBase(const GLObjectBase&) = delete;

	public:
		GLObjectBase(GLuint ObjectId) {
			this->ObjectId = ObjectId;
		}
		GLObjectBase(GLObjectBase&& other) {
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

		GLboolean IsBuffer() {
			return glIsBuffer(ObjectId);
		}
	};


}
