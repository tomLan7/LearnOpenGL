#include"glut.h"
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(25);
	glBegin(GL_POINTS);
	glVertex2f(0.2,0.3);
	glEnd();


	glLineWidth(5);
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	
	glVertex2f(0.5, 0.5);	
	glVertex2f(0,0);
	glEnd();
	glLineWidth(15);
	
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xAA);
	glBegin(GL_LINES);
	glVertex2f(0.2, 0.2);
	glVertex2f(-0.2, -0.3);
	glEnd();
	glFlush();
}
int main(int  argc,char* argv[]) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}