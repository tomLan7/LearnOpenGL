//��ͷ�ļ��Զ�������gl.h��glu.h
#include"glut.h"
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f,-0.5f,0.5f,0.5f);
	glFlush();
}
int main(int  argc,char* argv[]) {
	//��GLUT���г�ʼ��������������glut����ǰ����
	glutInit(&argc,argv);
	//������ʾ��ʽ��RGB��ɫ���������ǡ�
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("��һ��OpenGL����");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}