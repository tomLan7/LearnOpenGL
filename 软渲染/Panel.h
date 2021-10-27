#pragma once
#include"Color3B.h"
#include<SDL/SDL.h>
#include"Init.h"
namespace lan {
	class Window;
	//画布类，该画布存储一副图像，可以绘点和获得某个点像素坐标，该画布具体实现方式不重要
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
		//TODO: 目前写出边界抛的异常不是想要的，可能需要特定一个异常类型
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


