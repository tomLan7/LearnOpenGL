#include "LanGlut.h"
#include<iostream>
using namespace std;

static void _InitGlew() {
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error:" << glewGetErrorString(res) << endl;
		exit(1);
	}
	else {
		cout << "GLEW初始化成功" << endl;
	}
}
static void (*_renderFuncHandler)();
/*只有显示函数是必须设置，其他的不设置也可以，所以不需要兜底
static void (*_reshapeFuncHandler)(int width, int height);
static void (*_keyboardFuncHandler)(unsigned char key, int x, int y);
static void (*_mouseFuncHandler)(int button, int state, int x, int y);
static void (*_motionFuncHandler)(int x, int y);
static void (*_passiveMotionFuncHandler)(int x, int y);
static void (*_idleFuncHandler)(void);*/


void LanGlut::SetDisplayFunc(void (*func)(void)) {
	_renderFuncHandler = func;
}

void LanGlut::TriggerTimer(unsigned int msecs,
	void (*func)(int value), int value) {
	glutTimerFunc(msecs,func,value);
}

static void _DefaultRenderHandler() {
	cout << "default render function call"<<endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
static void _DefaultReshapeHandler(int width, int height) {
	cout << "default reshape function call width:"<<width <<" height:"<< height << endl;
}

static void _DefaultKeyboardHandler(unsigned char key, int x, int y) {
	cout << "default keyboard function call key:"<<key<<" x:" << x << " y:" << y << endl;
}
static void _DefaultMouseHandler(int button, int state, int x, int y) {
	cout << "default mouse function call button:"<<button<<" state:"<<state<<" x:" << x << " y:" << y << endl;
}
static void _DefaultMotionHandler(int x, int y) {
	cout << "default motion function call x:" << x << " y:" << y << endl;
}

static void _DefaultPassiveMotionHandler(int x, int y) {
	cout << "default passive motion function call x:" << x << " y:" << y << endl;
}

static void _DefaultIdleHandler() {
	cout << "default idle call"<< endl;
}

void LanGlut::SetReshapeFunc(void (*func)(int width, int height)) {
	glutReshapeFunc(func);
}

void LanGlut::SetKeyboardFunc(void (*func)(unsigned char key, int x, int y)) {
	glutKeyboardFunc(func);
}

void LanGlut::SetMouseFunc(void (*func)(int button, int state, int x, int y)) {
	glutMouseFunc(func);
}

void LanGlut::SetMotionFunc(void (*func)(int x, int y)) {
	glutMotionFunc(func);
}

void LanGlut::SetPassiveMotionFunc(void (*func)(int x, int y)) {
	glutPassiveMotionFunc(func);
}

void LanGlut::SetIdleFunc(void (*func)(void)) {
	glutIdleFunc(func);
}

void LanGlut::Init(int& argcp, char** argv) {
    glutInit(&argcp, argv);
	//参考这里，留着以后扩展 https://www.opengl.org/resources/libraries/glut/spec3/node12.html#SECTION00033000000000000000
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lanGlut Learning");

	_InitGlew();
	LanGlut::SetDisplayFunc(_DefaultRenderHandler);

	LanGlut::SetReshapeFunc(_DefaultReshapeHandler);
	LanGlut::SetKeyboardFunc(_DefaultKeyboardHandler);
	LanGlut::SetMouseFunc(_DefaultMouseHandler);
	LanGlut::SetMotionFunc(_DefaultMotionHandler);
	LanGlut::SetPassiveMotionFunc(_DefaultPassiveMotionHandler);
	LanGlut::SetIdleFunc(_DefaultIdleHandler);
}

void LanGlut::MainLoop() {
	glutDisplayFunc(_renderFuncHandler);
	/*除了显示函数，其他函数不需要兜底机制
	glutReshapeFunc(_reshapeFuncHandler);
	glutKeyboardFunc(_keyboardFuncHandler);
	glutMouseFunc(_mouseFuncHandler);
	glutMotionFunc(_motionFuncHandler);
	glutPassiveMotionFunc(_passiveMotionFuncHandler);
	glutIdleFunc(_idleFuncHandler);
	*/
	glutMainLoop();
}

void LanGlut::SetWindowTitle(const string& titleName) {
	glutSetWindowTitle(titleName.c_str());
}

