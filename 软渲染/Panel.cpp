
#include "Panel.h"
#include"Window.h"
using namespace lan;
lan::Panel::Panel(SDL_Surface* surface) {
	this->surface=surface;
	renderer = SDL_CreateSoftwareRenderer(surface);
}

lan::Panel::Panel(Window* surface):Panel(SDL_GetWindowSurface(surface->SDL_window()))
{
}

void lan::Panel::setDrawColor(Color3B color)
{
	drawColor = color;
}

Color3B lan::Panel::getDrawColor()
{
	return drawColor;
}

void lan::Panel::setPix(int x, int y, Color3B color)
{
	if (SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,255);
	SDL_RenderDrawPoint(renderer,x,y);
	SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, 255);

	if (SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}
}

void lan::Panel::setPix(int x, int y)
{
	setPix(x,y,drawColor);
}

void lan::Panel::Clear(bool userDrawColor)
{
	if (userDrawColor) {
		SDL_RenderClear(renderer);
	}
	else {
		setDrawColor(Color3B::WHITE);
		SDL_RenderClear(renderer);
		setDrawColor(drawColor);

	}
}

Color3B lan::Panel::getPix(int x, int y)
{
	if (x<0||x >= surface->w ||y<0|| y >= surface->h) {
		throw "´íÎóµÄsurfaceË÷ÒýÖµ";
	}
	if (SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}
	Color3B color;
	SDL_GetRGB(*(Uint32*)(((unsigned char)surface->pixels)+y*surface->pitch+x*surface->format->BytesPerPixel),surface->format,
		&color.r,&color.g,&color.b);

	if (SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}
	return color;
}
