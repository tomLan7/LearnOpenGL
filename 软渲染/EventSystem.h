#pragma once
#include<SDL/SDL.h>
namespace std {
	class EventSystem {
    public:
		static void debugLoop() {
            bool quit = false;
            SDL_Event event;
            while (!quit) {
                SDL_WaitEvent(&event);
                switch (event.type) {
                case SDL_QUIT://退出事件
                    SDL_Log("quit");
                    quit = true;
                    break;
                default:
                    SDL_Log("event type:%d", event.type);
                }
            }
		}
        static void freeLoop() {
            bool quit = false;
            SDL_Event event;
            while (!quit) {
                SDL_WaitEvent(&event);

                switch (event.type) {
                case SDL_QUIT://退出事件
                    SDL_Log("quit");
                    quit = true;
                    break;
                }
            }
        }
	};
}