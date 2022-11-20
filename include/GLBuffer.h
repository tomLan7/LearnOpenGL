#pragma once
#include<exception>
#include"GLDef.h"
namespace lan {
	//����һ������������
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
		/// �󶨵�ǰ��������ָ��Target
		/// </summary>
		/// <param name="target"></param>
		void BindBuffer(Target_Type target) {
			glBindBuffer(Target2GLenum(target), id);
		}

		/// <summary>
		/// ��ָ�������Target���
		/// </summary>
		/// <param name="target"></param>
		static void UnBindBuffer(Target_Type target) {
			glBindBuffer(Target2GLenum(target), 0);
		}
	};
}

