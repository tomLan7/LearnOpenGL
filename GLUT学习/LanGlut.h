#pragma once
#define GLEW_STATIC
#include"GLHeader.h"
#ifdef __APPLE__
#include<glut/glut.h>
#else
#include<GL/glut.h>
#endif

#include<string>
/// <summary>
/// 参考GLUT教程 https://www.jianshu.com/p/86f8ce123de1
/// </summary>
struct LanGlut {
    //初始化Glut，必须第一条调用
    static void Init(int& argcp, char** argv);
    /// <summary>
    /// 设置绘图回调函数。如果不设置就用默认的绘制函数，只显示但不进行任何操作
    /// </summary>
    /// <param name="func"></param>
    static void SetDisplayFunc(void (*func)(void));
    //进入Glut循环，必须最后一条调用
    static void MainLoop();

    /// <summary>
    /// 设置窗口标题
    /// </summary>
    /// <param name="titleName"></param>
    static void SetWindowTitle(const std::string& titleName);

    /// <summary>
    /// 交换双缓冲的缓冲区，让后台缓冲区显示出来。
    /// </summary>
    static void SwapBuffers() {
        glutSwapBuffers();
    }

    /// <summary>
    /// 可选的设置重新设置大小函数。
    /// </summary>
    /// <param name="func"></param>
    static void SetReshapeFunc(void (*func)(int width, int height));

    /// <summary>
    /// 可选的键盘事件
    /// </summary>
    /// <param name="func"></param>
    static void SetKeyboardFunc(void (*func)(unsigned char key, int x, int y));

    /// <summary>
    /// 可选的鼠标事件
    /// </summary>
    /// <param name="func"></param>
    static void SetMouseFunc(void (*func)(int button, int state, int x, int y));

    /// <summary>
    /// 可选的拖动事件。传NULL即可禁用。
    /// </summary>
    /// <param name="func"></param>
    static void SetMotionFunc(void (*func)(int x, int y));

    /// <summary>
    /// 可选的拖动事件。传NULL即可禁用。
    /// </summary>
    /// <param name="func"></param>
    static void SetPassiveMotionFunc(void (*func)(int x, int y));

    /// <summary>
    /// 可选的停止事件。传NULL即可禁用。
    /// </summary>
    /// <param name="func"></param>
    static void SetIdleFunc(void (*func)(void));

    /// <summary>
    /// 触发一个一次性定时器。
    /// </summary>
    /// <param name="msecs">单位毫秒</param>
    /// <param name="func"></param>
    /// <param name="value">参数的值。</param>
    static void TriggerTimer(unsigned int msecs,
        void (*func)(int value), int value);

    /// <summary>
    /// post不是立刻调用。所以不用Trigger。标记需要绘制
    /// </summary>
    static void PostRedisplay() {
        glutPostRedisplay();
    }

    /// <summary>
    /// 特殊按键，如方向键等
    /// </summary>
    /// <param name="func"></param>
    static void SetSpecialKeyFunc(void (*func)(int key, int x, int y)) {
        glutSpecialFunc(func);
    }

    static lan::Vector2F GetScreenSize() {
        auto swidth = glutGet(GLUT_SCREEN_WIDTH);
        auto sheight = glutGet(GLUT_SCREEN_HEIGHT);
        return {swidth,sheight};
    }

    static lan::Vector2F GetWindowSize() {
        auto wwidth = glutGet(GLUT_WINDOW_WIDTH);
        auto wheight = glutGet(GLUT_WINDOW_HEIGHT);
        return { wwidth,wheight };
    }

    /*
    * 还欠缺的事件回调
    * glutVisibilityFunc    设置窗口可见性的回调
    * glutEntryFunc         进入或离开窗口
    * Spaceball设备相关，ButtonBox设备，Dials设备，Tablet设备，
    * glutMenuStatusFunc    弹出菜单回调
    * int glutIgnoreKeyRepeat(int repeatMode); 禁用keyboard的repeatMode 传递0，开启auto repeat，非0则禁用auto repeat。
    * Void glutKeyboardUpFunc(void (*func)(unsigned char key,int x,int y));
    * Void glutSpecialUpFunc(void (*func)(int key,int x,int y));
    */
};


