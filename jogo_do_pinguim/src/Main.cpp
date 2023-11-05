#include <SDL2/SDL.h>

#include "game/Game/Game.hpp"
#include "game/TitleState/TitleState.hpp"

int main(int, char **)
{
    Game &game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();
    return 0;
}