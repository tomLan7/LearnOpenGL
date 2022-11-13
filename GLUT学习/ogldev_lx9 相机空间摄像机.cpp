
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"Shader.h"
#include"Matrix4F.h"
#include"Pipeline.h"
#include"GLUTWindow.h"
using namespace std;
using namespace lan;
GLuint VBO1;
GLuint IBO1;
lan::ShaderProgram* shader;
lan::Pipeline p;
float Rate = 0;
void IdleFunc() {
	Rate += 0.002;

	//p.initPerspectiveProj(160.0f, 1.f, 0.1f, 1.0f);
	auto v=lan::Vector3F(0, 0, 1);
	v.rotateY(Rate);
	p.initCamera(Vector3F(0,0,0),v, lan::Vector3F(0,1,0 ));
	//p.initCamera(Vector3F(0,0,0), lan::Vector3F(0, 1, 0), lan::Vector3F(0,0,1 ));
	glutPostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	/*测试问题代码
	Vector4F test1(0,1,sin(Rate)+0.5,1);
	Vector4F test2(1, 0, sin(Rate) + 0.5, 1);
	Vector4F test3(1, 1, sin(Rate) + 0.5, 1);
	Vector4F test4(0, 0, sin(Rate) + 0.5, 1);
	cout << test1 << endl;
	cout << test2 << endl;
	cout << test3 << endl;
	cout << test4 << endl;
	cout << Matrix4F::OrthoProjTransform(-1, 1, -1, 1, 0, 1) * test1 << endl;
	cout << Matrix4F::OrthoProjTransform(-1, 1, -1, 1, 0, 1) * test2 << endl;
	cout << Matrix4F::OrthoProjTransform(-1, 1, -1, 1, 0, 1) * test3 << endl;
	cout << Matrix4F::OrthoProjTransform(-1, 1, -1, 1, 0, 1) * test4 << endl;
	cout << "下一轮"<< endl;
	*/
	//能看到是因为，OpenGL的NDC的z范围是-1到1，所以摄像机旋转后还是能看见。
	shader->Uniform("gMat",Matrix4F::OrthoProjTransform(-1,1,-1,1,0,1)* p.GetCameraTransform());
	//shader->Uniform("gMat",Matrix4F::PersProjTransform(120,1,0,1)* p.GetCameraTransform());
	//shader->Uniform("gMat", Matrix4F());
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

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

	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(0.f, 0.1f, 1.f);
	Vertices[1] = lan::Vector3F(0.f, 0.8f, 0.5f);
	Vertices[2] = lan::Vector3F(.9f, -.9f, 0.5f);
	Vertices[3] = lan::Vector3F(-0.9f, -0.9f, 0.5f);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	unsigned int Indices[] = { 0, 3, 1,
						   1, 3, 2,
						   2, 3, 0,
						   0, 1, 2 };
	glGenBuffers(1, &IBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx7.vert", "lx9.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	glutMainLoop();
	return 0;
}