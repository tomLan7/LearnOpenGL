#pragma once
#include<string>
#include<SDL/SDL.h>
namespace lan {
    //代表一个窗口，一个窗口可以加载一个Panel或多个Panel，并当Panel更新时自动刷新显示。——观察者模式
	class Window
	{
		SDL_Window* window;
	public:
		SDL_Window* SDL_window() {
			return window;
		}
        Window(const std::string& title = "title", int width = 640, int height = 480)
        {
            window = SDL_CreateWindow(
                title.c_str(),                  // window title
                SDL_WINDOWPOS_UNDEFINED,           // initial x position
                SDL_WINDOWPOS_UNDEFINED,           // initial y position
                width,                               // width, in pixels
                height,                               // height, in pixels
                SDL_WINDOW_SHOWN // flags - see below
            );

            // Check that the window was successfully created
            if (window == NULL) {
                // In the case that the window could not be made...
                printf("Could not create window: %s\n", SDL_GetError());
                return;
            }
        }
		~Window() {
			SDL_DestroyWindow(window);
		}
	};

}

