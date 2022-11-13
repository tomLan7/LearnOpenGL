
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"Shader.h"
#include"GLUTWindow.h"
using namespace std;
using namespace lan;
GLuint VBO1;
lan::ShaderProgram* shader;

float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	glutPostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Uniform("testScale",Rate);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	InitGLUT(&argc, argv);
	GLUTWindow window("Lx3");
	InitGLEW();
	window.setDisplayFunc(Render);

	glutIdleFunc(IdleFunc);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[3];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.0f);
	Vertices[1] = lan::Vector3F(1.0f, -1.0f, 0.0f);
	Vertices[2] = lan::Vector3F(0.0f, 1.0f, 0.0f);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx5.vert", "lx4.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	glutMainLoop();
	return 0;
}