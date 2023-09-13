#include <SDL2/SDL.h>

#include "app/Game/Game.hpp"

int main(int argc, char **argv)
{
    Game &game = Game::GetInstance();
    game.Run();
    return 0;
}