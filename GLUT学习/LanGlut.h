#pragma once
#define GLEW_STATIC
#include"GL/glew.h"
#include<glut.h>
#include<string>
/// <summary>
/// �ο�GLUT�̳� https://www.jianshu.com/p/86f8ce123de1
/// </summary>
struct LanGlut {
    //��ʼ��Glut�������һ������
    static void Init(int& argcp, char** argv);
    /// <summary>
    /// ���û�ͼ�ص���������������þ���Ĭ�ϵĻ��ƺ�����ֻ��ʾ���������κβ���
    /// </summary>
    /// <param name="func"></param>
    static void SetDisplayFunc(void (*func)(void));
    //����Glutѭ�����������һ������
    static void MainLoop();

    /// <summary>
    /// ���ô��ڱ���
    /// </summary>
    /// <param name="titleName"></param>
    static void SetWindowTitle(const std::string& titleName);

    /// <summary>
    /// ����˫����Ļ��������ú�̨��������ʾ������
    /// </summary>
    static void SwapBuffers() {
        glutSwapBuffers();
    }

    /// <summary>
    /// ��ѡ�������������ô�С������
    /// </summary>
    /// <param name="func"></param>
    static void SetReshapeFunc(void (*func)(int width, int height));

    /// <summary>
    /// ��ѡ�ļ����¼�
    /// </summary>
    /// <param name="func"></param>
    static void SetKeyboardFunc(void (*func)(unsigned char key, int x, int y));

    /// <summary>
    /// ��ѡ������¼�
    /// </summary>
    /// <param name="func"></param>
    static void SetMouseFunc(void (*func)(int button, int state, int x, int y));

    /// <summary>
    /// ��ѡ���϶��¼�����NULL���ɽ��á�
    /// </summary>
    /// <param name="func"></param>
    static void SetMotionFunc(void (*func)(int x, int y));

    /// <summary>
    /// ��ѡ���϶��¼�����NULL���ɽ��á�
    /// </summary>
    /// <param name="func"></param>
    static void SetPassiveMotionFunc(void (*func)(int x, int y));

    /// <summary>
    /// ��ѡ��ֹͣ�¼�����NULL���ɽ��á�
    /// </summary>
    /// <param name="func"></param>
    static void SetIdleFunc(void (*func)(void));

    /// <summary>
    /// ����һ��һ���Զ�ʱ����
    /// </summary>
    /// <param name="msecs">��λ����</param>
    /// <param name="func"></param>
    /// <param name="value">������ֵ��</param>
    static void TriggerTimer(unsigned int msecs,
        void (*func)(int value), int value);
    /*
    * ��Ƿȱ���¼��ص�
    * glutVisibilityFunc    ���ô��ڿɼ��ԵĻص�
    * glutEntryFunc         ������뿪����
    * glutSpecialFunc       ���ⰴ��
    * Spaceball�豸��أ�ButtonBox�豸��Dials�豸��Tablet�豸��
    * glutMenuStatusFunc    �����˵��ص�
    * 
    */
};


