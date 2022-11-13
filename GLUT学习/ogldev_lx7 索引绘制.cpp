
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"Shader.h"
#include"Matrix4F.h"
#include"Camera.h"
#include"Pipeline.h"
#include"GLUTWindow.h"

using namespace std;
using namespace lan;
GLuint VBO1;
GLuint IBO1;
lan::ShaderProgram* shader;
lan::Matrix4F M_trans;
lan::Matrix4F M_rotate;
lan::Matrix4F M_scaling;
lan::Pipeline p;

float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	p.initRotate(0,0,Rate*30);
	p.initWorldOffset(sin(Rate), 0, 0);
	p.initScale(sin(Rate), sin(Rate), sin(Rate));
	
	glutPostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->Uniform("gMat", p.GetTransNoProj());
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO1);
	glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	InitGLUT(&argc, argv);
	GLUTWindow window("Lx7");
	InitGLEW();
	window.setDisplayFunc(Render);
	window.setIdleFunc(IdleFunc);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.5f);
	Vertices[1] = lan::Vector3F(0.f, -1.0f, 1.0f);
	Vertices[2] = lan::Vector3F(1.0f, -1.0f, 0.5f);
	Vertices[3] = lan::Vector3F(0.f, 1.0f, 0.5f);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	unsigned int Indices[] = { 0, 3, 1,
						   1, 3, 2,
						   2, 3, 0,
						   0, 1, 2 };
	glGenBuffers(1, &IBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx7.vert", "lx6.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	glutMainLoop();
	return 0;
}