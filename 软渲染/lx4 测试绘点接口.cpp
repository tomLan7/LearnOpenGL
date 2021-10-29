#include<iostream>
#include"Window.h"
#include"Panel.h"
using namespace std;
using namespace lan;

//我走了88
#include<vector>
#include<string>
#include<map>
using namespace std;

int main(int argc, char* argv[]) {
	Window window ("test setPix");
	Panel panel(&window);
	panel.setDrawColor(Color3B::BLACK);
	panel.Clear(false);
	for (float i = 0; i < 3.14;i+=0.01) {
		panel.setPix(i*100,sin(i)*100+200);
	}
    for (float i = 0; i <200; i += 0.01) {
        panel.setPix(i, i);
    }
	panel.flush();
	window.flush();
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
	return 0;
}