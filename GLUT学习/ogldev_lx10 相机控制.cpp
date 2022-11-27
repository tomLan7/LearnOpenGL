#include"GLHeader.h"
#include<iostream>
#include"Vector3F.h"
#include"Matrix4F.h"
#include<glm/gtc/quaternion.hpp>
#include "LanGlut.h"
using namespace std;
using namespace lan;
GLBuffer* VBO1;
GLBuffer* EBO1;
lan::ShaderProgram* shader;
lan::Pipeline p;
void IdleFunc() {
	
	LanGlut::PostRedisplay();
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	p.initPerspectiveProj(60.0f, 1.f, 0.3f, 1000.f);
	shader->Uniform("gMat", p.GetTransByCameraAndPerspective());
	ElementBufferTarget::DrawElements(EBO1, GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
}

int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("相机空间变换摄像机的运用");
	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);
	LanGlut::SetSpecialKeyFunc([](int key, int x, int y) {p.SpecialKeyboardCB(key,x,y); });
	p.initCamera(Vector3F(0, 0, 0), lan::Vector3F(0, 0, 1), lan::Vector3F(0, 1, 0));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(0.f, 0.1f, 1.f);
	Vertices[1] = lan::Vector3F(0.f, 0.8f, 0.5f);
	Vertices[2] = lan::Vector3F(.9f, -.9f, 0.5f);
	Vertices[3] = lan::Vector3F(-0.9f, -0.9f, 0.5f);
	VBO1 = new GLBuffer();
	ArrayBufferTarget::BufferData(VBO1, sizeof(Vertices), Vertices, Usage_Type::STATIC_DRAW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	unsigned int Indices[] = { 0, 3, 1,
						   1, 3, 2,
						   2, 3, 0,
						   0, 1, 2 };
	EBO1 = new GLBuffer();
	ElementBufferTarget::BufferData(EBO1, sizeof(Indices), Indices, Usage_Type::STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx7.vert", "lx9.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	LanGlut::MainLoop();
	return 0;
}