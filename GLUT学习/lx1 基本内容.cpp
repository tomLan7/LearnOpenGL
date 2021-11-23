//该头文件自动包含了gl.h和glu.h
#include"glut.h"
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f,-0.5f,0.5f,0.5f);
	glFlush();
}
int main(int  argc,char* argv[]) {
	//对GLUT进行初始化。必须在其他glut函数前调用
	glutInit(&argc,argv);
	//设置显示方式，RGB颜色，还可以是。
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}