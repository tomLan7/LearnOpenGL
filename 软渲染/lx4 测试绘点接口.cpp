#include<iostream>
#include"Window.h"
#include"Panel.h"
#include"EventSystem.h"
using namespace std;
using namespace lan;
int main(int argc, char* argv[]) {
	Window window ("test setPix");//创建窗口
	Panel panel(window);//创建画布
	panel.setDrawColor(Color3B::WHITE);//设置默认绘制颜色为白色
    panel.clear();//清空画面为黑屏。
    //绘制一个正弦函数到画布
    for (float i = 0; i < 3.14; i += 0.01) {
        panel.setPix(i * 100, sin(i) * 100 +  200);
    }
    //绘制一个直线到画布
    for (float i = 0; i < 200; i += 0.01) {
        panel.setPix(i, i);
    }
    panel.flush();//输出画布结果到窗口
    window.flush();//交换缓冲区。因为显示都是用 双缓冲机制

    EventSystem::debugLoop();
	return 0;
}