
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"GLUTWindow.h"
using namespace std;
using namespace lan;
GLuint VBO1;
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glDrawArrays(GL_POINTS, 0, 1);
	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	GLUTWindow window("Lx2");
	window.setDisplayFunc(Render);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr<<"Error:"<<glewGetErrorString(res)<<endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[1];
	Vertices[0] = lan::Vector3F(0.0f, 0.0f, 0.0f);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glutMainLoop();
	return 0;
}