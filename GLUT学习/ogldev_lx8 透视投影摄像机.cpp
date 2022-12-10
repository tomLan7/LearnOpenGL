#include"GLHeader.h"
#include<iostream>
#include"Vector3F.h"
#include"Matrix4F.h"
#include"LanGlut.h"
using namespace std;
using namespace lan;

GLBuffer* vbo1;
GLBuffer* ibo1;
lan::ShaderProgram* shader;
lan::Matrix4F M_trans;
lan::Matrix4F M_rotate;
lan::Matrix4F M_scaling;
lan::Pipeline p;
float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	p.initWorldRotate(0, 0, 0);
	p.initWorldScale(1, 1, 1);
	p.initWorldOffset(1, 0, 0);
	p.initPerspectiveProj(sin(Rate)*60.0f+120,1.f, 0.3f, 1.0f);
	//p.initPerspectiveProj(120, 1.f, 0.3f+sin(Rate)*0.6, 1.0f);
	glutPostRedisplay();
}
//GLUT用于绘制的回调函数
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->Uniform("gMat", p.GetTransByPerspective());//使用透视功能，不使用相机矩阵。
	//vbo1->BindBuffer(Target_Type::ARRAY_BUFFER);
	ElementBufferTarget::DrawElements(ibo1, GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	//GLBuffer::UnBindBuffer(Target_Type::ARRAY_BUFFER);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {

	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("透视投影摄像机的运用");
	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);
	/*camera.SetPerspectiveProj(50.0f, 1.f, 0.3f, 5.0f);
	cout << camera.m_persProj * lan::Vector4F(0, 0,4.5, 1)<<endl;*/

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(0.f, 0.1f, 1.f);
	Vertices[1] = lan::Vector3F(0.f, 0.8f, 0.0f);
	Vertices[2] = lan::Vector3F(.9f, -.9f, 0.f);
	Vertices[3] = lan::Vector3F(-0.9f, -0.9f, 0.f);
	vbo1 = new GLBuffer();
	ArrayBufferTarget::BufferData(vbo1, sizeof(Vertices), Vertices, EUsage_Type::STATIC_DRAW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	unsigned int Indices[] = { 0, 3, 1,
						   1, 3, 2,
						   2, 3, 0,
						   0, 1, 2 };
	ibo1 = new GLBuffer();
	ElementBufferTarget::BufferData(ibo1,sizeof(Indices), Indices, EUsage_Type::STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx7.vert", "lx6.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	LanGlut::MainLoop();
	return 0;
}