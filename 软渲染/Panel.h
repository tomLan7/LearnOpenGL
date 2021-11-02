#pragma once
#include"Color3B.h"
#include<SDL/SDL.h>
#include"Init.h"
namespace lan {
	class Window;
	//�����࣬�û����洢һ��ͼ�񣬿��Ի��ͻ��ĳ�����������꣬�û�������ʵ�ַ�ʽ����Ҫ����Ӧ��ʾ����֡���档
	class Panel
	{
		SDL_Surface* surface;
		SDL_Renderer* renderer;
	public:
		Panel(SDL_Surface* surface) {
			this->surface = surface;
			renderer = SDL_CreateSoftwareRenderer(surface);
		}
		Panel(Window* window) :Panel(SDL_GetWindowSurface(window->SDL_window()))
		{
		}
		Panel(Window& window) :Panel(SDL_GetWindowSurface(window.SDL_window()))
		{
		}
		void setDrawColor(Color3B color)
		{
			SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,SDL_ALPHA_OPAQUE);
		}
		Color3B getDrawColor()
		{
			Color3B color;
			SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, 0);
			return color;
		}
		//TODO: Ŀǰд���߽��׵��쳣������Ҫ�ģ�������Ҫ�ض�һ���쳣����
		void setPix(int x, int y, Color3B color)
		{
			if (SDL_MUSTLOCK(surface)) {
				SDL_LockSurface(surface);
			}
			auto preColor = getDrawColor();
			setDrawColor(color);
			SDL_RenderDrawPoint(renderer, x, surface->h - y - 1);
			setDrawColor(preColor);

			if (SDL_MUSTLOCK(surface)) {
				SDL_UnlockSurface(surface);
			}
		}
		void setPix(int x, int y)
		{
			if (SDL_MUSTLOCK(surface)) {
				SDL_LockSurface(surface);
			}
			SDL_RenderDrawPoint(renderer, x, surface->h - y - 1);
			if (SDL_MUSTLOCK(surface)) {
				SDL_UnlockSurface(surface);
			}
		}
		void clear(bool userDrawColor = false)
		{
			if (userDrawColor) {
				SDL_RenderClear(renderer);
			}
			else {
				auto preColor = getDrawColor();
				setDrawColor(Color3B::BLACK);
				SDL_RenderClear(renderer);
				setDrawColor(preColor);

			}
		}
		Color3B getPix(int x, int y)
		{
			if (x<0 || x >= surface->w || y<0 || y >= surface->h) {
				throw "�����surface����ֵ";
			}
			if (SDL_MUSTLOCK(surface)) {
				SDL_LockSurface(surface);
			}
			Color3B color;
			SDL_Color a;
			SDL_GetRGB(*(Uint32*)(((unsigned char)surface->pixels) + y * surface->pitch + x * surface->format->BytesPerPixel), surface->format,
				&color.r, &color.g, &color.b);

			if (SDL_MUSTLOCK(surface)) {
				SDL_UnlockSurface(surface);
			}
			return color;
		}
		void flush() {
			SDL_RenderPresent(renderer);
		}
		~Panel() {
			SDL_DestroyRenderer(renderer);
		}
	};
}


