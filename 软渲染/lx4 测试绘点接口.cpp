#include<iostream>
#include"Window.h"
#include"Panel.h"
#include"EventSystem.h"
using namespace std;
using namespace lan;
int main(int argc, char* argv[]) {
	Window window ("test setPix");//��������
	Panel panel(window);//��������
	panel.setDrawColor(Color3B::WHITE);//����Ĭ�ϻ�����ɫΪ��ɫ
    panel.clear();//��ջ���Ϊ������
    //����һ�����Һ���������
    for (float i = 0; i < 3.14; i += 0.01) {
        panel.setPix(i * 100, sin(i) * 100 +  200);
    }
    //����һ��ֱ�ߵ�����
    for (float i = 0; i < 200; i += 0.01) {
        panel.setPix(i, i);
    }
    panel.flush();//����������������
    window.flush();//��������������Ϊ��ʾ������ ˫�������

    EventSystem::debugLoop();
	return 0;
}