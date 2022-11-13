#pragma once
#include<exception>
//代表一个缓冲区对象
class GLBuffer
{
	GLuint id;
	
public:
	enum Target_Type {
		ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER,
	};
	enum Usage_Type {
		STATIC_DRAW
	};
	~GLBuffer() {
		if (id != 0) {
			glDeleteBuffers(1, &id);
			id = 0;
		}
	}

	GLBuffer() {
		glGenBuffers(1,&id);
	}
	GLBuffer(GLuint id) {
		this->id = id;
	}
	/// <summary>
	/// 绑定当前缓冲区到指定Target
	/// </summary>
	/// <param name="target"></param>
	void BindBuffer(Target_Type target) {
		glBindBuffer(Target2GLenum(target),id);
	}

	/// <summary>
	/// 让指定区域的Target解绑
	/// </summary>
	/// <param name="target"></param>
	static void UnBindBuffer(Target_Type target) {
		glBindBuffer(Target2GLenum(target),0);
	}

	/// <summary>
	/// 往target和Usage_Type所对应的目标内存传输数据。
	/// </summary>
	/// <param name="target"></param>
	/// <param name="data"></param>
	/// <param name="len"></param>
	/// <param name="usage"></param>
	static void BufferData(Target_Type target,const void* data,size_t len, Usage_Type usage) {
		glBufferData(Target2GLenum(target), len,data,Usage2GLenum(usage));
	}

	static GLenum Target2GLenum(Target_Type target) {
		switch (target)
		{
		case ARRAY_BUFFER:
			return GL_ARRAY_BUFFER;
		case ELEMENT_ARRAY_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			break;
		}
		throw new std::exception("未支持的BuffTarget类型枚举");
	}
	static GLenum Usage2GLenum(Usage_Type target) {
		switch (target)
		{
		case STATIC_DRAW:
			return GL_STATIC_DRAW;
		default:
			break;
		}
		throw new std::exception("未支持的STATIC_DRAW类型枚举");
	}
};

