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
lan::Matrix4F M_trans;
lan::Matrix4F M_rotate;
lan::Matrix4F M_scaling;
lan::Pipeline p;

float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	p.initWorldRotate(0,0,Rate*30);
	p.initWorldOffset(sin(Rate), 0, 0);
	p.initWorldScale(sin(Rate), sin(Rate), sin(Rate));
	
	glutPostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->Uniform("gMat", p.GetTransNoProj());
	VBO1->BindBuffer(ETarget_Type::ARRAY_BUFFER);
	//EBO1->BindBuffer(Target_Type::ELEMENT_ARRAY_BUFFER);这句不加会怎么样？
	ElementBufferTarget::DrawElements(EBO1,GL_TRIANGLES,12,GL_UNSIGNED_INT,0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//为什么带上这句会报错不带Bind那行就会报错？
	//glBindBuffer(GL_ARRAY_BUFFER, 0);这句不加会怎么样？

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("索引矩阵的运用");
	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[4];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.5f);
	Vertices[1] = lan::Vector3F(0.f, -1.0f, 1.0f);
	Vertices[2] = lan::Vector3F(1.0f, -1.0f, 0.5f);
	Vertices[3] = lan::Vector3F(0.f, 1.0f, 0.5f);
	VBO1 = new GLBuffer();
	ArrayBufferTarget::BufferData(VBO1, sizeof(Vertices), Vertices, EUsage_Type::STATIC_DRAW);

	unsigned int Indices[] = { 0, 3, 1,
						   1, 3, 2,
						   2, 3, 0,
						   0, 1, 2 };
	EBO1 = new GLBuffer();
	ElementBufferTarget::BufferData(EBO1,sizeof(Indices), Indices, EUsage_Type::STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx7.vert", "lx6.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标

	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	LanGlut::MainLoop();
	return 0;
}