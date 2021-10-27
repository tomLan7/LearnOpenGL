#pragma once
#include"Color3B.h"
#include<SDL/SDL.h>
#include"Init.h"
namespace lan {
	class Window;
	//�����࣬�û����洢һ��ͼ�񣬿��Ի��ͻ��ĳ�����������꣬�û�������ʵ�ַ�ʽ����Ҫ
	class Panel
	{
		SDL_Surface* surface;
		SDL_Renderer* renderer;
		Color3B drawColor;
	public:
		Panel(SDL_Surface* surface);
		Panel(Window* surface);
		void setDrawColor(Color3B color);
		Color3B getDrawColor();
		//TODO: Ŀǰд���߽��׵��쳣������Ҫ�ģ�������Ҫ�ض�һ���쳣����
		void setPix(int x, int y,Color3B color);
		void setPix(int x,int y);
		void Clear(bool userDrawColor=true);
		Color3B getPix(int x, int y);
		void flush() {
			SDL_RenderPresent(renderer);
		}
		~Panel() {
			SDL_DestroyRenderer(renderer);
		}
	};
}


