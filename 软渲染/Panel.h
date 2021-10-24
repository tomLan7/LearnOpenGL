#pragma once
#include"Color3B.h"
#include<SDL/SDL.h>
namespace lan {
	class Window;
	//�����࣬�û����洢һ��ͼ�񣬿��Ի��ͻ��ĳ�����������꣬�û�������ʵ�ַ�ʽ����Ҫ
	class Panel
	{
		SDL_Renderer* renderer;
		Color3B currentColor;
	public:
		Panel(Window* window);
		void setPix(int x, int y,Color3B color);
		void setPix(int x,int y);
		//TODO:get�������ʵ�֣�Ŀǰ�����Լ���װ��set��������¼��ÿ�β�����ʵ��
		Color3B getPix(int x, int y);
		void flush() {
			SDL_RenderPresent(renderer);
		}
		~Panel() {
			SDL_DestroyRenderer(renderer);
		}
	};
}


