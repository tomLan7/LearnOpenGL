#include"LanGlut.h"
#include<iostream>
using namespace std;
void Render() {
	cout << "测试新的Render" << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	LanGlut::SwapBuffers();
}
int main(int argc,char** argv) {
	LanGlut::Init(argc, argv);
	//LanGlut::SetDisplayFunc(Render);
	LanGlut::SetWindowTitle("你好");
	LanGlut::SetIdleFunc(NULL);
	LanGlut::SetPassiveMotionFunc(NULL);
	LanGlut::TriggerTimer(1000, [](int value) {cout << "测试定时器" << endl; 
	}, 5);

	LanGlut::MainLoop();
}