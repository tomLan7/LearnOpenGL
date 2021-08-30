#include"glut.h"
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK, GL_POINT);
	glBegin(GL_POLYGON);
	glVertex2d(0.1,0.2);
	glVertex2d(0.3, 0.4);
	glVertex2d(0.2, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(-0.1, -0.2);
	glVertex2d(-0.2, -0.1);
	glVertex2d(-0.3, -0.4);
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