
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include"GLUTWindow.h"
#include"Shader.h"
#include"GlBuffer.h"
using namespace std;
using namespace lan;
GLBuffer* vbo1;
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	vbo1->BindBuffer(GLBuffer::Target_Type::ARRAY_BUFFER);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	InitGLUT(&argc, argv);
	GLUTWindow window("Lx4");
	InitGLEW();
	window.setDisplayFunc(Render);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[3];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.0f);
	Vertices[1] = lan::Vector3F(1.0f, -1.0f, 0.0f);
	Vertices[2] = lan::Vector3F(0.0f, 1.0f, 0.0f);
	vbo1 = new GLBuffer();
	
	vbo1->BindBuffer(GLBuffer::Target_Type::ARRAY_BUFFER);

	GLBuffer::BufferData(GLBuffer::Target_Type::ARRAY_BUFFER, Vertices,sizeof(Vertices), GLBuffer::Usage_Type::STATIC_DRAW);
	auto shader = lan::ShaderProgram::CreateFromVertexAndFragmentPath("lx4.vert", "lx4.frag");
	GLint Location=shader->GetAttribLocation("Position");//获得对应顶点属性的下标
	glEnableVertexAttribArray(Location);
	glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
 
	shader->User();
	glutMainLoop();
	return 0;
}