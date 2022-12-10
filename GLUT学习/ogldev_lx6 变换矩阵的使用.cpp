
#include"GLHeader.h"
#include<iostream>
#include"Matrix4F.h"
#include "LanGlut.h"
using namespace std;
using namespace lan;

GLBuffer* vbo;
lan::ShaderProgram* shader;
lan::Matrix4F M_trans;
lan::Matrix4F M_rotate;
lan::Matrix4F M_scaling;
float Rate = 0;
void IdleFunc() {
	Rate += 0.001;
	M_rotate = lan::Matrix4F::RotationZ(Rate);
	M_trans = lan::Matrix4F::Translate({ sin(Rate),0,0 });
	M_scaling = lan::Matrix4F::Scale({sin(Rate),sin(Rate) ,sin(Rate) });
	LanGlut::PostRedisplay();
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->Uniform("gScale", M_scaling);
	shader->Uniform("gRotate", M_rotate);
	shader->Uniform("gTranslate", M_trans);

	ArrayBufferTarget::DrawArrays(vbo,GL_TRIANGLES,0,3);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetWindowTitle("变换矩阵的运用");
	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);
	LanGlut::SetDisplayFunc(Render);

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[3];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.0f);
	Vertices[1] = lan::Vector3F(1.0f, -1.0f, 0.0f);
	Vertices[2] = lan::Vector3F(0.0f, 1.0f, 0.0f);
	vbo = new GLBuffer();
	ArrayBufferTarget::BufferData(vbo, sizeof(Vertices), Vertices, EUsage_Type::STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx6.vert", "lx6.frag");
	GLint Location = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	cout << "顶点属性下标为" << Location << endl;
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader->User();
	LanGlut::MainLoop();
	return 0;
}