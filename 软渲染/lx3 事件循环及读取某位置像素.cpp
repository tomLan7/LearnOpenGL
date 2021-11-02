#include <iostream>

#include <SDL/SDL.h>
using namespace std;
SDL_Color getPix(SDL_Window* window, int x, int y) {
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    auto format=surface->format;
    
    SDL_LockSurface(surface);
    Uint32* data = (Uint32*)surface->pixels;
    SDL_Color color;
    //cout<<"每个像素占"<<(int)surface->format->BytesPerPixel << endl;
    //cout << "宽" << surface->w << "高" << surface->h << endl;
    SDL_GetRGB(data[y*surface->pitch/4+x],surface->format,&color.r, &color.g, &color.b);
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);
    return color;
}
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow(
        "SDL2 Draw Window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_SHOWN // flags - see below
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
     {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 15, 23, 44, 255);
        SDL_RenderDrawPoint(renderer, 10, 10);

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
    }
     
     auto c1=getPix(window, 10, 15);
     auto c2 = getPix(window, 10, 10);
     cout << (int)c1.r << (int)c1.g << (int)c1.b << endl;
     cout << (int)c2.r << (int)c2.g << (int)c2.b << endl;
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
    //destory renderer
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;

}