#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

using namespace std;

class State;
class Game
{
public:
    Game(const string &title, int width, int height);
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();

private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
};