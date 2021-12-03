
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"Shader.h"
#include"Matrix4F.h"
#include"Camera.h"
using namespace std;
GLuint VBO1;
GLuint IBO1;
lan::ShaderProgram* shader;
lan::Matrix4F M_trans;
lan::Matrix4F M_rotate;
lan::Matrix4F M_scaling;
lan::Pipeline camera;
float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	camera.Rotate(0, 0, 0);
	camera.WorldPos(sin(Rate), 0, 0);
	camera.Scale(1, 1, 1);

	camera.setPerspectiveProj(160.0f,1.f, 0.3f, 1.0f);
	glutPostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->Uniform("gMat", camera.GetTransByPerspective());
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glDrawElements(GL_TRIANGLES,12, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 02");
	glutDisplayFunc(Render);
	glutIdleFunc(IdleFunc);
	/*camera.SetPerspectiveProj(50.0f, 1.f, 0.3f, 5.0f);
	cout << camera.m_persProj * lan::Vector4F(0, 0,4.5, 1)<<endl;*/

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error:" << glewGetErrorString(res) << endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(0.f, 0.1f, 1.f);
	Vertices[1] = lan::Vector3F(0.f, 0.8f, 0.0f);
	Vertices[2] = lan::Vector3F(.9f, -.9f, 0.f);
	Vertices[3] = lan::Vector3F(-0.9f, -0.9f, 0.f);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
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