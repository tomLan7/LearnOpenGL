
#include"GLHeader.h"
#include<iostream>
#include"Vector3F.h"
#include"Matrix4F.h"
#include"LanGlut.h"
using namespace std;
using namespace lan;
GLBuffer* VBO1;
GLBuffer* EBO1;
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
	//能看到是因为，OpenGL的NDC的z范围是-1到1，所以摄像机旋转后还是能看见。
	shader->Uniform("gMat",Matrix4F::OrthoProjTransform(-1,1,-1,1,0,1)* p.GetCameraTransform());
	ElementBufferTarget::DrawElements(EBO1, GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("相机空间变换摄像机的运用");
	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);

	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(0.f, 0.1f, 1.f);
	Vertices[1] = lan::Vector3F(0.f, 0.8f, 0.5f);
	Vertices[2] = lan::Vector3F(.9f, -.9f, 0.5f);
	Vertices[3] = lan::Vector3F(-0.9f, -0.9f, 0.5f);
	VBO1 = new GLBuffer();
	ArrayBufferTarget::BufferData(VBO1, sizeof(Vertices), Vertices, Usage_Type::STATIC_DRAW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
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