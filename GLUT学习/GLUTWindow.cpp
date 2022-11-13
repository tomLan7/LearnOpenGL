
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include "GLUTWindow.h"
#include<iostream>
using namespace std;

void lan::InitGLUT(int* argc, char** argv)
{
	glutInit(argc, argv);
}

void lan::InitGLEW()
{
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error:" << glewGetErrorString(res) << endl;
		exit(1);
	}

}
