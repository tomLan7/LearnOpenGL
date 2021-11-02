#include<iostream>
#include"Window.h"
#include"Panel.h"
#include"Render.h"
#include<memory>
#include"EventSystem.h"
using namespace std;
using namespace lan;

int main(int argc, char* argv[]) {
    shared_ptr<int> arr;
    Window window("test setPix");
    Panel panel(&window);
    panel.setDrawColor(Color3B::WHITE);
    panel.clear(false);
    Render render(panel);
    render.drawLineByDDA(25,25,90,90);
    render.drawLineByDDA(25, 25, 90, 20);
    render.drawLineByDDA(25, 25, 30, 90);
    render.drawLineByDDA(25, 25, 25, 90);
    render.flush();
    window.flush();
    
    EventSystem::debugLoop();

    return 0;
}