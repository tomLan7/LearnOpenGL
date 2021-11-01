#include<iostream>
#include"Window.h"
#include"Panel.h"
#include"Render.h"
#include<memory>
using namespace std;
using namespace lan;

int main(int argc, char* argv[]) {
    shared_ptr<int> arr;
    Window window("test setPix");
    Panel panel(&window);
    panel.setDrawColor(Color3B::BLACK);
    panel.Clear(false);
    Render render(panel);
    render.drawLineByEquation(25,25,90,90);
    render.drawLineByEquation(25, 25, 90, 20);
    render.drawLineByEquation(25, 25, 20, 90);
    render.flush();
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