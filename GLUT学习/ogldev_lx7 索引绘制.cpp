
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"Shader.h"
#include"Matrix4F.h"
using namespace std;
GLuint VBO1;
GLuint IBO1;
lan::ShaderProgram* shader;
lan::Matrix4F M_trans;
lan::Matrix4F M_rotate;
lan::Matrix4F M_scaling;
float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	M_rotate = lan::Matrix4F::RotationZ(Rate);
	M_trans = lan::Matrix4F::Translation({ sin(Rate),0,0 });
	M_scaling = lan::Matrix4F::Scaling({ sin(Rate),sin(Rate) ,sin(Rate) });
	glutPostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->Uniform("gScale", M_scaling);
	shader->Uniform("gRotate", M_rotate);
	shader->Uniform("gTranslate", M_trans);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO1);
	glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);

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
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error:" << glewGetErrorString(res) << endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.0f);
	Vertices[1] = lan::Vector3F(0.f, -1.0f, 1.0f);
	Vertices[2] = lan::Vector3F(1.0f, -1.0f, 0.0f);
	Vertices[3] = lan::Vector3F(0.f, 1.0f, 0.0f);
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
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx6.vert", "lx6.frag");
	GLint Location = shader->GetAttribLocation("Position");//��ö�Ӧ�������Ե��±�
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	glutMainLoop();
	return 0;
}