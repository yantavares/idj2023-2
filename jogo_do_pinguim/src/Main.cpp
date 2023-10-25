#include <SDL2/SDL.h>

#include "game/Game/Game.hpp"

int main(int argc, char **argv)
{
    srand(time(NULL));
    Game &game = Game::GetInstance();
    game.Run();
    return 0;
}