#pragma once
#include<exception>
#include"GLDef.h"
namespace lan {
	//代表一个缓冲区对象
	class GLBuffer
	{
		GLuint id;

	public:

		~GLBuffer() {
			if (id != 0) {
				glDeleteBuffers(1, &id);
				id = 0;
			}
		}

		GLBuffer() {
			glGenBuffers(1, &id);
		}
		GLBuffer(GLuint id) {
			this->id = id;
		}
		/// <summary>
		/// 绑定当前缓冲区到指定Target
		/// </summary>
		/// <param name="target"></param>
		void BindBuffer(Target_Type target) {
			glBindBuffer(Target2GLenum(target), id);
		}

		/// <summary>
		/// 让指定区域的Target解绑
		/// </summary>
		/// <param name="target"></param>
		static void UnBindBuffer(Target_Type target) {
			glBindBuffer(Target2GLenum(target), 0);
		}
	};
}

