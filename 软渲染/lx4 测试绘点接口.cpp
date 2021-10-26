#include<iostream>
#include"Window.h"
#include"Panel.h"
using namespace std;
using namespace lan;
int main(int argc, char* argv[]) {
	Window window ("test setPix");
	Panel panel(&window);
	panel.setDrawColor(Color3B::BLACK);
	panel.Clear(false);
	for (float i = 0; i < 3.14;i+=0.01) {
		panel.setPix(i*100,sin(i)*100+200);
	}
	panel.flush();
	window.flush();
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_QUIT://ÍË³öÊÂ¼þ
            SDL_Log("quit");
            quit = true;
            break;
        default:
            SDL_Log("event type:%d", event.type);
        }
    }
	return 0;
}