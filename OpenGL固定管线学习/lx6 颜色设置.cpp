#include"glut.h"
#include<stdio.h>
void myDisplay() {
	glColor3ub(255,242,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-1.f,-1.f,0.2f,0.2f);


	//glColor3ub(220, 240, 60);
	//glIndexi(2);
	glRectf(-0.2f, -0.2f, 1.f, 1.f);
	glFlush();
}
int main(int  argc,char* argv[]) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutGet(GLUT_WINDOW_COLORMAP_SIZE);
	//glutSetColor(0,0,0,255);
	//printf("颜色表大小%d",glutGet(GLUT_WINDOW_COLORMAP_SIZE));
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}