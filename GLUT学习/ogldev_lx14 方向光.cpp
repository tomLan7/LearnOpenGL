#include"GLHeader.h"
#include<iostream>
#include"Vector3F.h"
#include"Matrix4F.h"
#include"Quaternion.h"
#include<glm/gtc/quaternion.hpp>
#include "LanGlut.h"
#include <windows.h>
using namespace std;
using namespace lan;

GLBuffer* VBO1;
GLBuffer* EBO1;
Texture* texture1;
ShaderProgram* shader;
Pipeline p;
DirectionalLight light;

float t;
void IdleFunc() {
	t += 0.01;
	//cout << "rate" << rate << "四元数" << quat << "欧拉角" << euler << endl;
	LanGlut::PostRedisplay();
	light.Direction = Vector3F(0.5, cos(t), sin(t));
}

void Render() {
	//cout << "绘图" << endl;
	p.ClearBuffer(EClear_Buffer::COLOR_BUFFER_BIT| EClear_Buffer::DEPTH_BUFFER_BIT);

	p.initPerspectiveProj(60.0f, 1.f, 0.3f, 1000.f);
	shader->Uniform("gWVP", p.GetTransByPerspective() * p.GetCameraTransform());
	shader->Uniform("gWorld",p.getWorldTransform());
	texture1->Bind(3);
	shader->UniformTextureUnit("gSampler", 3);
	shader->Uniform("gDirectionalLight", light);
	ElementBufferTarget::DrawElements(EBO1, GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	LanGlut::SwapBuffers();
}
int main(int  argc, char* argv[]) {
	LanGlut::Init(argc, argv);
	LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("使用纹理");
	light.Direction = Vector3F(1,0.2,0.3);
	light.DiffuseIntensity = 0.5;
	light.AmbientIntensity = 0.2;
	light.Color = Vector3F(0.5, 0.2, 0.8);
	LanGlut::SetIdleFunc(IdleFunc);
	LanGlut::SetPassiveMotionFunc(NULL);
	LanGlut::SetMotionFunc([](int x, int y) {
		auto windowSize = LanGlut::GetWindowSize();
		float h = x / windowSize.x * 360 - 180;
		float v = -(y / windowSize.y * 180 - 90);
		cout << "横角度:" << h << "\t纵角度:" << v << endl;
		p.getMainCamera().setHVAngle(h, v);
		});
	LanGlut::SetKeyboardFunc([](unsigned char key, int x, int y) {
		if (key == 'q') {
			exit(0);
		}
		});
	LanGlut::SetSpecialKeyFunc([](int key, int x, int y) {
		p.SpecialKeyboardCB(key, x, y);
		cout << "key： " << key << "和x： " << x << "和y： " << y << endl;
		cout << p.getMainCamera().toString() << endl;
		});

	LanGlut::SetKeyboardFunc([](unsigned char key, int x, int y) {
		p.ASCIIKeyboardCB(key, x, y);
		cout << "key： " << key << "和x： " << x << "和y： " << y << endl;
		cout << p.getMainCamera().toString() << endl;
		});
	p.initCamera(Vector3F(0, 0, 0), lan::Vector3F(0, 0, 1), lan::Vector3F(0, 1, 0));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	texture1 = new Texture("container.jpg");
	cout << "支持纹理单元数为" << Texture::GetMaxCombinedTextureImageUnitsCount() << endl;

	p.FontFace(EWrap_Direction::CounterClockwise);
	glCullFace(GL_BACK);//设置剔除面
	glEnable(GL_CULL_FACE);//开启背面剔除
	std::vector<Vertex> vertices = {
	Vertex(Vector3F(-1.0f, -1.0f, 0.5773f), Vector2F(0.0f, 0.0f)),
	Vertex(Vector3F(0.0f, -1.0f, -1.15475), Vector2F(0.5f, 0.0f)),
	Vertex(Vector3F(1.0f, -1.0f, 0.5773f), Vector2F(1.0f, 0.0f)),
	Vertex(Vector3F(0.0f, 1.0f, 0.0f), Vector2F(0.5f, 1.0f)) };

	VBO1 = new GLBuffer();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	p.EnableFeatures(EFeatures::DEPTH_TEST);

	vector<int >Indices= { 0,1,3,
						   1, 2, 3,
						   0,3,2,
						   0, 2,1 };

	Vertex::InitNormal(vertices,Indices);
	ArrayBufferTarget::BufferData(VBO1, vertices, EUsage_Type::STATIC_DRAW);


	EBO1 = new GLBuffer();
	ElementBufferTarget::BufferData(EBO1, Indices, EUsage_Type::STATIC_DRAW);
	shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx14.vert", "lx14.frag");
	GLint Location1 = shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	GLint Location2 = shader->GetAttribLocation("TexCoord");//获得对应顶点属性的下标
	GLint Location3 = shader->GetAttribLocation("Normal");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location1);
	glEnableVertexAttribArray(Location2);
	glEnableVertexAttribArray(Location3);
	glVertexAttribPointer(Location1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(Location2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(Location3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

	shader->User();
	LanGlut::MainLoop();
	return 0;
}