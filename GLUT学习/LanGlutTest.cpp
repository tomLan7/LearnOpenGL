#include"LanGlut.h"
#include<iostream>
using namespace std;
void Render() {
	cout << "�����µ�Render" << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	LanGlut::SwapBuffers();
}
int main(int argc,char** argv) {
	LanGlut::Init(argc, argv);
	//LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("���");
	LanGlut::SetIdleFunc(NULL);
	LanGlut::SetPassiveMotionFunc(NULL);
	LanGlut::TriggerTimer(1000, [](int value) {cout << "���Զ�ʱ��" << endl; 
	}, 5);

	LanGlut::MainLoop();
}