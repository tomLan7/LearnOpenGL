#pragma once
#include"Color3B.h"
namespace lan {
	//�����࣬�û����洢һ��ͼ�񣬿��Ի��ͻ��ĳ�����������꣬�û�������ʵ�ַ�ʽ����Ҫ
	class Panel
	{
		void setPix(int x, int y,Color3B color);
		Color3B getPix(int x, int y);
	};
}


