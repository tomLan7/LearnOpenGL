
#include "Panel.h"
#include"Window.h"
using namespace lan;
lan::Panel::Panel(Window* window) {
	renderer = SDL_CreateRenderer(window->SDL_window(), -1, 0);
}

void lan::Panel::setPix(int x, int y, Color3B color)
{
	SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b,255);
	setPix(x,y);
	SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, 255);

}

void lan::Panel::setPix(int x, int y)
{
	SDL_RenderDrawPoint(renderer, x, y);
}

Color3B lan::Panel::getPix(int x, int y)
{
}
