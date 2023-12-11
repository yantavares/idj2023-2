#include <SDL2/SDL.h>
#include <ctime>

#include "game/Game/Game.hpp"
#include "../StageState/StageState.hpp" // Inclua o caminho correto para StageState

int main(int argc, char **argv)
{
    srand(time(NULL));

    Game &game = Game::GetInstance();
    
    // Cria uma instância de StageState e dá push no jogo
    StageState* stageState = new StageState();
    
    game.Push(stageState);

    // Executa o jogo
    game.Run();

    return 0;
}
