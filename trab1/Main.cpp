#include <SDL2/SDL.h>

#include "Game.hpp"

int main(int argc, char **argv)
{
    Game game("Yan Tavares, 202041323 :)))", 1024, 600);
    game.Run();
    return 0;
}