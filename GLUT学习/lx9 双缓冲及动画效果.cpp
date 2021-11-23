#include"glut.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
//计算帧数的函数
double CalFrequencyEveryFrame()
{
    static clock_t current;
    static clock_t pre;
    current = clock();
    if (pre == 0) pre = current-10;
    double rtn= ((current- pre)/ (double)CLOCKS_PER_SEC);//得到时间，该帧和上一帧距离多少秒
    pre = current;
    return 1/rtn;//得到一秒多少帧
}


// 太阳、地球和月亮 
// 假设每个月都是 30 天 
// 一年 12 个月，共是 360 天 
static int day = 15; // day 的变化：从 0 到 359 
void myDisplay(void)
{
    double FPS = CalFrequencyEveryFrame();
    printf("FPS = %f\n", FPS);
    //深度缓冲，当某个像素前没有其他遮挡时再绘制。通过比较后深度值发生变化了，会进行更新深度缓冲区的操作。可以有效提高3D绘制效率
    //glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);//投影矩阵模式
    glLoadIdentity();//重置当前矩阵为单位矩阵。用一个4×4的单位矩阵来替换当前矩阵
    gluPerspective(75, 1, 1, 400000000);//设置透视视角。视角 为75度。
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1); //45度角看向0点
    // 绘制红色的“太阳” 
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(69600000, 20, 20);
    // 绘制蓝色的“地球” 
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(150000000, 0.0f, 0.0f);
    glutSolidSphere(15945000, 20, 20);
    // 绘制黄色的“月亮” 
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(day / 30.0 * 360.0 - day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(38000000, 0.0f, 0.0f);
    glutSolidSphere(4345000, 20, 20);

    glFlush();
}
void myIdle(void)
{
    /* 新的函数，在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果 */
    ++day;
    if (day >= 360)
        day = 0;
    myDisplay();
    _sleep(50);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("太阳，地球和月亮");

    glutDisplayFunc(&myDisplay);

    glutIdleFunc(&myIdle);//设置CPU在空闲时间会调用的函数
    glutMainLoop();
    return 0;
}