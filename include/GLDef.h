#pragma once
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<exception>

/// <summary>
/// 直接封装OpenGL中的一些内容，不包含逻辑，不依赖其他逻辑类，只定义
/// </summary>
namespace lan {
	enum class ETarget_Type {
		//VAO 顶点数组对象
		ARRAY_BUFFER,
		//索引数组对象
		ELEMENT_ARRAY_BUFFER,
	};
	enum class EUsage_Type {
		STATIC_DRAW,
	};

	///可以供glClear使用的参数
	enum class EClear_Buffer {
		None = 0,
		//颜色缓冲
		COLOR_BUFFER_BIT = 1<<0,
		//深度缓冲
		DEPTH_BUFFER_BIT = 1<<1,
		//模板缓冲
		STENCIL_BUFFER_BIT = 1<<3,
	};

	///可以供glClear使用的参数
	enum class EWrap_Direction {
		//逆时针时
		CounterClockwise,
		//顺时针时
		Clockwise,
	};

	enum class ESide {
		FRONT,
		BACK,
	};

	enum class EFeatures{
		DEPTH_TEST
	};

	static GLenum Target2GLenum(ETarget_Type target) {
		switch (target)
		{
		case ETarget_Type::ARRAY_BUFFER:
			return GL_ARRAY_BUFFER;
		case ETarget_Type::ELEMENT_ARRAY_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			break;
		}
		throw new std::exception("未支持的ETarget_Type类型枚举");
	}

	static GLenum Usage2GLenum(EUsage_Type target) {
		switch (target)
		{
		case EUsage_Type::STATIC_DRAW:
			return GL_STATIC_DRAW;
		default:
			break;
		}
		throw new std::exception("未支持的EUsage_Type类型枚举");
	}

	static EClear_Buffer operator | (EClear_Buffer a,EClear_Buffer b) {
		return (EClear_Buffer)((GLbitfield)a | (GLbitfield)b);
	}

	static EClear_Buffer operator & (EClear_Buffer a, EClear_Buffer b) {
		return (EClear_Buffer)((GLbitfield)a & (GLbitfield)b);
	}

	static GLbitfield  Buffer2GLbitfield(EClear_Buffer target) {
		GLbitfield result=0;
		if ((target & EClear_Buffer::COLOR_BUFFER_BIT) != EClear_Buffer::None) {
			result |= GL_COLOR_BUFFER_BIT;
		}
		if ((target & EClear_Buffer::DEPTH_BUFFER_BIT) != EClear_Buffer::None) {
			result |= GL_DEPTH_BUFFER_BIT;
		}
		if ((target & EClear_Buffer::STENCIL_BUFFER_BIT) != EClear_Buffer::None) {
			result |= GL_STENCIL_BUFFER_BIT;
		}
		return result;
	}

	static GLenum WrapDirection2GLenum(EWrap_Direction target) {
		switch (target)
		{
		case EWrap_Direction::Clockwise:
			return GL_CW;
		case EWrap_Direction::CounterClockwise:
			return GL_CCW;
		default:
			break;
		}
		throw new std::exception("未支持的EWrap_Direction类型枚举");
	}

	static GLenum Side2GLenum(ESide target) {
		switch (target)
		{
		case ESide::BACK:
			return GL_BACK;
		case ESide::FRONT:
			return GL_FRONT;
		default:
			break;
		}
		throw new std::exception("未支持的ESide类型枚举");
	}

	static GLenum Features2GLenum(EFeatures target) {
		switch (target)
		{
		case EFeatures::DEPTH_TEST:
			return GL_DEPTH_TEST;
		default:
			break;
		}
		throw new std::exception("未支持的EFeatures类型枚举");
	}

}
