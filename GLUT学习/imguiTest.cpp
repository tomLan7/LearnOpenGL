
#define GLEW_STATIC
#include"GL/glew.h"
#include"glut.h"
#include<iostream>
#include"Vector3F.h"
#include<imgui.h>
#include<backends/imgui_impl_glut.h>
using namespace std;
GLuint VBO1;

void ImGUIRender() {
	ImGui::Text("Hello, world %d", 123);
	ImGui::Button("Save");	
	char buf[512];
	ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
	float f;
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
}
void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	ImGUIRender();
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glDrawArrays(GL_TRIANGLES, 0, 3);



	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
	glutSwapBuffers();
}
int main(int  argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 02");
	glutDisplayFunc(Render);
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error:" << glewGetErrorString(res) << endl;
		return 1;
	}



	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	// FIXME: Consider reworking this example to install our own GLUT funcs + forward calls ImGui_ImplGLUT_XXX ones, instead of using ImGui_ImplGLUT_InstallFuncs().
	ImGui_ImplGLUT_Init();
	ImGui_ImplGLUT_InstallFuncs();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	lan::Vector3F Vertices[3];
	Vertices[0] = lan::Vector3F(-1.0f, -1.0f, 0.0f);
	Vertices[1] = lan::Vector3F(1.0f, -1.0f, 0.0f);
	Vertices[2] = lan::Vector3F(0.0f, 1.0f, 0.0f);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glutMainLoop();
	return 0;
}