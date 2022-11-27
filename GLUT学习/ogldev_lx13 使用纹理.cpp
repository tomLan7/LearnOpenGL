#include"GLHeader.h"
#include<iostream>
#include"Vector3F.h"
#include"Matrix4F.h"
#include"Quaternion.h"
#include<glm/gtc/quaternion.hpp>
#include "LanGlut.h"
#include<Magick++.h>
#include <windows.h>
using namespace std;
using namespace lan;
GLBuffer* VBO1;
GLBuffer* EBO1;
lan::ShaderProgram* shader;
lan::Pipeline p;

Quaternion startQ = Quaternion::fromEulerAngle(0, 90, 0);
Quaternion endQ = Quaternion::fromEulerAngle(0, 0, 180);


float rate = 0;

void IdleFunc() {
	//rate += 0.005;
	if (rate > 1)rate -= 1;
	auto quat = Quaternion::slerp(startQ, endQ, rate);
	auto euler = quat.toEuler() * Rad2Deg;

	p.initWorldRotate(euler);
	//cout << "rate" << rate << "��Ԫ��" << quat << "ŷ����" << euler << endl;
	LanGlut::PostRedisplay();
}

void Render() {
	//cout << "��ͼ" << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	p.initPerspectiveProj(60.0f, 1.f, 0.3f, 1000.f);
	shader->Uniform("gWVP", p.GetTransByPerspective() * p.GetCameraTransform() * p.getWorldTransform());
	ElementBufferTarget::DrawElements(EBO1, GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
}

int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("ʹ������");

	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);
	LanGlut::SetMotionFunc([](int x, int y) {
		auto windowSize = LanGlut::GetWindowSize();
		float h = x / windowSize.x * 360 - 180;
		float v = -(y / windowSize.y * 180 - 90);
		cout << "��Ƕ�:" << h << "\t�ݽǶ�:" << v << endl;
		p.getMainCamera().setHVAngle(h, v);
		});
	LanGlut::SetKeyboardFunc([](unsigned char key, int x, int y) {
		if (key == 'q') {
			exit(0);
		}
		});
	LanGlut::SetSpecialKeyFunc([](int key, int x, int y) {
		p.SpecialKeyboardCB(key, x, y);
		std::cout << "key��" << key << "��x��" << x << "��y��" << y << std::endl;
	std::cout << p.getMainCamera().toString() << std::endl;
		});

	LanGlut::SetKeyboardFunc([](unsigned char key, int x, int y) {
		p.ASCIIKeyboardCB(key, x, y);
		std::cout << "key��" << key << "��x��" << x << "��y��" << y << std::endl;
		std::cout << p.getMainCamera().toString() << std::endl;
		});
	p.initCamera(Vector3F(0, 0, 0), lan::Vector3F(0, 0, 1), lan::Vector3F(0, 1, 0));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	Texture texture("container.jpg");
	lan::Vector3F oldVertices[4];
	oldVertices[0] = lan::Vector3F(0.f, 0.1f, 1.f);
	oldVertices[1] = lan::Vector3F(0.f, 0.8f, 0.5f);
	oldVertices[2] = lan::Vector3F(.9f, -.9f, 0.5f);
	oldVertices[3] = lan::Vector3F(-0.9f, -0.9f, 0.5f);

	Vertex Vertices[4] = {
	Vertex(Vector3F(-1.0f, -1.0f, 0.5773f), Vector2F(0.0f, 0.0f)),
	Vertex(Vector3F(0.0f, -1.0f, -1.15475), Vector2F(0.5f, 0.0f)),
	Vertex(Vector3F(1.0f, -1.0f, 0.5773f), Vector2F(1.0f, 0.0f)),
	Vertex(Vector3F(0.0f, 1.0f, 0.0f), Vector2F(0.5f, 1.0f)) };
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
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx13.vert", "lx13.frag");
	GLint Location1 = shader->GetAttribLocation("Position");//��ö�Ӧ�������Ե��±�
	GLint Location2 = shader->GetAttribLocation("TexCoord");//��ö�Ӧ�������Ե��±�
	glEnableVertexAttribArray(Location1);
	glEnableVertexAttribArray(Location2);
	glVertexAttribPointer(Location1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(Location2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	shader->User();
	LanGlut::MainLoop();
	return 0;
}