#pragma once
#include<Vector3F.h>
#include<string>
#include <functional>
namespace lan {
	class GLUTWindow
	{
	public:
		//���ڵı�ʶ
		int id;

		GLUTWindow(std::string title,int x=100, int y=100, int width=1024, int height=768) 
		{
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
			glutInitWindowSize(width, height);
			glutInitWindowPosition(x, y);
			id=glutCreateWindow(title.c_str());
		}
		void setDisplayFunc(void(*callback)() ) {
			glutDisplayFunc(callback);
		}
		void setIdleFunc(void(*callback)()) {
			glutIdleFunc(callback);
		}
	};
	extern void InitGLUT(int* argcp, char** argv);
	//������GLUTCreateWindow֮���ʼ��GLEW������ᱨ��δʶ��İ汾
	extern void InitGLEW();
}

