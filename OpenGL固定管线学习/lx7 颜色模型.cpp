#include <math.h> 
#include"glut.h"
#include<stdio.h>
const GLdouble Pi = 3.1415926536;
void myDisplay(void)
{
    int i;
     glShadeModel(GL_FLAT); 
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
   
    for (i = 0; i <= 8; ++i)
    {

        //0x0000 0100 //0x0000 0010 //0x0000 0001
        printf("颜色%d,%d,%d\n", i & 0x04, i & 0x02, i & 0x01);
        glColor3f(i & 0x04, i& 0x02, i & 0x01);
        glVertex2f(cos(i * Pi / 4), sin(i * Pi / 4));
    }
    glEnd();
    glFlush();
}
int main(int  argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    
    glutCreateWindow("第一个OpenGL程序");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}