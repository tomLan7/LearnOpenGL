#pragma once
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"

namespace lan {
	enum class Target_Type {
		//VAO 顶点数组对象
		ARRAY_BUFFER,
		//索引数组对象
		ELEMENT_ARRAY_BUFFER,
	};
	enum class Usage_Type {
		STATIC_DRAW,
	};

	static GLenum Target2GLenum(Target_Type target) {
		switch (target)
		{
		case Target_Type::ARRAY_BUFFER:
			return GL_ARRAY_BUFFER;
		case Target_Type::ELEMENT_ARRAY_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			break;
		}
		throw new std::exception("未支持的BuffTarget类型枚举");
	}
	static GLenum Usage2GLenum(Usage_Type target) {
		switch (target)
		{
		case Usage_Type::STATIC_DRAW:
			return GL_STATIC_DRAW;
		default:
			break;
		}
		throw new std::exception("未支持的STATIC_DRAW类型枚举");
	}
}
