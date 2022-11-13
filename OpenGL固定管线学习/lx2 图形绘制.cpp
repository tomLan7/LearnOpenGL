//该头文件自动包含了gl.h和glu.h

#include"OGLan.h"
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}
int main(int  argc, char* argv[]) {
	//设置显示方式，RGB颜色，还可以是。

	OGLan l(argc,argv);


	l.initDisplayMode(GLUT_RGB | GLUT_SINGLE);
	l.initWindowPosition(200,300);
	l.initWindowSize(800,600);
	l.createWindow("测试LanOG类");
	//l.set2DRange(800,600);
	paint->drawLined(0.1,0.2,100,100);
	paint->drawPointd(0.2, 0.2);
	paint->drawCircle(0.2,0.2,0.5);
	paint->drawCircle(0.6, 0.6, 0.2);
	paint->fullCircle(-0.2,-0.2,0.2);
	paint->fullCircle(-0.2, 0.7, 0.3);
	l.exec();
	return 0;
}