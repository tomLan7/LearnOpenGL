#pragma once
#include<Vector3F.h>
#include<string>
#include <functional>
namespace lan {
	class GLUTWindow
	{
	public:
		//窗口的标识
		int id;

		GLUTWindow(std::string title,int x=100, int y=100, int width=1024, int height=768) 
		{
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
			glutInitWindowSize(width, height);
			glutInitWindowPosition(x, y);
			id=glutCreateWindow(title.c_str());
		}
		void DisplayFunc(void(*callback)() ) {
			glutDisplayFunc(callback);
		}
	};
	static void InitGLUT(int* argcp, char** argv);
}

