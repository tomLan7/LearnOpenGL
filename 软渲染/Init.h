#pragma once
#include<iostream>
#include<SDL/SDL.h>
class InitSDL{
	static InitSDL* instance;
	InitSDL() {
		if (SDL_Init(SDL_INIT_VIDEO)==0) {
			std::cout << "SDL init success" << std::endl;
		}
		else {
			std::cout << "SDL init error" << std::endl;

		}
	}
public:
	static InitSDL* getInstance() {
		
	}
	
};