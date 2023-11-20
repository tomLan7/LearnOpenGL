#pragma once
#define GLEW_STATIC
#include"GL/glew.h"
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
		DEPTH_TEST,
		CULL_FACE,
	};

	enum class EErrorType {
		INVALID_ENUM,//枚举参数超出范围
		INVALID_VALUE,//数值超出范围
		INVALID_OPERATION,//当前状态中操作非法
		OUT_OF_MEMORY,//内存不足
		NO_ERROR,//没有错误
	};

	static GLenum Error2GLenum(EErrorType error) {
		//帮我写
        switch (error)
		{
		case EErrorType::INVALID_ENUM:
			return GL_INVALID_ENUM;
		case EErrorType::INVALID_VALUE:
			return GL_INVALID_VALUE;
		case EErrorType::INVALID_OPERATION:
			return GL_INVALID_OPERATION;
		case EErrorType::OUT_OF_MEMORY:
			return GL_OUT_OF_MEMORY;
		case EErrorType::NO_ERROR:
			return GL_NO_ERROR;
		default:
			break;
		}
		throw new std::exception("未支持的EErrorType类型枚举");
	}

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
		case EFeatures::CULL_FACE:
            return GL_CULL_FACE;
		default:
			break;
		}
		throw new std::exception("未支持的EFeatures类型枚举");
	}
	struct Color {
		float r;
		float g;
		float b;
		float a;
		Color(float r, float g, float b, float a = 1) :r(r), g(g), b(b), a(a) {
			clamp();
		}

		void clamp() {
			r = r > 1.0f ? 1.0f : r;
			r = r < 0 ? 0 : r;
			g = g > 1.0f ? 1.0f : g;
			g = g < 0 ? 0 : g;
			b = b > 1.0f ? 1.0f : b;
			b = b < 0 ? 0 : b;
			a = a > 1.0f ? 1.0f : a;
			a = a < 0 ? 0 : a;
		}
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Yellow;
		static const Color Blue;
		static const Color Magenta;
		static const Color Cyan;
		static const Color DarkGray;
		static const Color LightGray;
		static const Color Brown;
		static const Color PumpkinOrange;
		static const Color PastelPink;
		static const Color BarneyPurple;
		static const Color While;
	};
}
