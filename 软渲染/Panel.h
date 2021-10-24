#pragma once
#include"Color3B.h"
#include<SDL/SDL.h>
namespace lan {
	class Window;
	//画布类，该画布存储一副图像，可以绘点和获得某个点像素坐标，该画布具体实现方式不重要
	class Panel
	{
		SDL_Renderer* renderer;
		Color3B currentColor;
	public:
		Panel(Window* window);
		void setPix(int x, int y,Color3B color);
		void setPix(int x,int y);
		//TODO:get方法如何实现？目前打算自己封装好set方法，记录下每次操作来实现
		Color3B getPix(int x, int y);
		void flush() {
			SDL_RenderPresent(renderer);
		}
		~Panel() {
			SDL_DestroyRenderer(renderer);
		}
	};
}


