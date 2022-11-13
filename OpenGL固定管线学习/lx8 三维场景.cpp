#include"glut.h"
#include<stdlib.h>
#include<time.h>
#include<stdio.h>


// ̫������������� 
// ����ÿ���¶��� 30 �� 
// һ�� 12 ���£����� 360 �� 
static int day =15; // day �ı仯���� 0 �� 359 
void myDisplay(void)
{
    //��Ȼ��壬��ĳ������ǰû�������ڵ�ʱ�ٻ��ơ�ͨ���ȽϺ����ֵ�����仯�ˣ�����и�����Ȼ������Ĳ�����������Ч���3D����Ч��
    //glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);//ͶӰ����ģʽ
    glLoadIdentity();//���õ�ǰ����Ϊ��λ������һ��4��4�ĵ�λ�������滻��ǰ����
    gluPerspective(75, 1,1, 400000000);//����͸���ӽǡ��ӽ� Ϊ75�ȡ�
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1); //45�Ƚǿ���0��
    // ���ƺ�ɫ�ġ�̫���� 
glColor3f(1.0f, 0.0f, 0.0f);
glutSolidSphere(69600000, 20, 20);
// ������ɫ�ġ����� 
glColor3f(0.0f, 0.0f, 1.0f);
glRotatef(day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
glTranslatef(150000000, 0.0f, 0.0f);
glutSolidSphere(15945000, 20, 20);
// ���ƻ�ɫ�ġ������� 
glColor3f(1.0f, 1.0f, 0.0f);
glRotatef(day / 30.0 * 360.0 - day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
glTranslatef(38000000, 0.0f, 0.0f);
glutSolidSphere(4345000, 20, 20);

glFlush();
glutSwapBuffers();//��Ϊ��˫���壬������һ��������������ϵͳ����һ������������������������չʾ
}
void myIdle(void)
{
    /* �µĺ������ڿ���ʱ���ã������ǰ����������ƶ�һ�첢���»��ƣ��ﵽ����Ч�� */
    ++day;
    if (day >= 360)
        day = 0;
    myDisplay();
    _sleep(33);
  
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("̫�������������");

    glutDisplayFunc(&myDisplay);
    
    glutIdleFunc(&myIdle);//����CPU�ڿ���ʱ�����õĺ���
    glutMainLoop();
    return 0;
}