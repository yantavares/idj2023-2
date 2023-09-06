#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main()
{
    SDL_Window *window = nullptr;

    SDL_Surface *window_surface = nullptr;
    SDL_Surface *image_surface = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    window_surface = SDL_GetWindowSurface(window);
    image_surface = SDL_LoadBMP("image.bmp");

    SDL_BlitSurface(image_surface, NULL, window_surface, NULL);

    SDL_UpdateWindowSurface(window);

    for (size_t i = 0; i < 100; i++)
    {
        SDL_PumpEvents();
    }

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_FreeSurface(image_surface);
    SDL_Quit();
}