
#include"GLHeader.h"
#include<iostream>
#include"LanGlut.h"
#include <Vector3F.h>
using namespace std;
using namespace lan;
GLBuffer* vbo1;
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	vbo1->BindBuffer(Target_Type::ARRAY_BUFFER);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("��ɫ��ʹ��");
	LanGlut::SetIdleFunc(NULL);
	LanGlut::SetPassiveMotionFunc(NULL);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	lan::Vector3F Vertices[3];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.0f);
	Vertices[1] = lan::Vector3F(1.0f, -1.0f, 0.0f);
	Vertices[2] = lan::Vector3F(0.0f, 1.0f, 0.0f);
	vbo1 = new GLBuffer();
	vbo1->BindBuffer(Target_Type::ARRAY_BUFFER);
	ArrayBufferTarget::BufferData(Vertices,sizeof(Vertices), Usage_Type::STATIC_DRAW);
	auto shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx4.vert", "lx4.frag");
	GLint location=shader->GetAttribLocation("Position");//��ö�Ӧ�������Ե��±�
	cout << "��Ӧ�����±���" << location << endl;
	//������Ӧ������Դ
	glEnableVertexAttribArray(location);
	//������Դ��������
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
 
	shader->User();
	LanGlut::MainLoop();
	return 0;
}