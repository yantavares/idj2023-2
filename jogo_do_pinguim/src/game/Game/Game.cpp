#include "Game.hpp"
#include "../InputManager/InputManager.hpp"
#include "../../components/Resources/Resources.hpp"

Game *Game::instance = nullptr;

Game::Game(char *title, int width, int height)
{
    if (instance == nullptr)
    {
        instance = this;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        throw std::runtime_error(std::string("Erro ao carregar SDL. ") + std::string(SDL_GetError()));
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        throw std::runtime_error(std::string("Erro ao carregar SDL_IMG. ") + std::string(SDL_GetError()));
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        throw std::runtime_error(std::string("Erro ao carregar SDL_MIX. ") + std::string(SDL_GetError()));
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        throw std::runtime_error(std::string("Erro ao executar Mix_OpenAudio. ") + std::string(SDL_GetError()));
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr)
    {
        throw std::runtime_error("Erro ao criar janela.");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        throw std::runtime_error("Erro ao criar renderer.");
    }

    if (TTF_Init() != 0)
    {
        throw std::runtime_error(std::string("Erro ao carregar SDL_Ttf. ") + std::string(SDL_GetError()));
    }

    srand(time(NULL));

    storedState = nullptr;
}


Game &Game::GetInstance()
{

    if (instance == nullptr)
    {
        instance = new Game("Yan Tavares, 202041323 :)", 1024, 600);
    }
    return *instance;
}

int Game::GetWidth()
{
    return width;
}

int Game::GetHeight()
{
    return height;
}



Game::~Game()
{
    if (storedState)
    {
        delete storedState;
    }

    while (!stateStack.empty())
    {
        stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game destroyed successfully\n";
}

State &Game::GetState()
{

    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

State &Game::GetCurrentState()
{

    return *stateStack.top();
}

void Game::Push(State *state)
{
    storedState = state;
}

void Game::CalculateDeltaTime()
{
    dt = (SDL_GetTicks() - frameStart);
    frameStart = SDL_GetTicks();
}

float Game::GetDeltaTime()
{
    return dt;
}


void Game::Run()
{
    if (storedState) {
        stateStack.emplace(storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }
    if(stateStack.empty()) {
        throw std::runtime_error("Game iniciado sem estado inicial.");
    }

    while (!stateStack.empty() && stateStack.top()->QuitRequested() == false)
    {
        if (stateStack.top()->PopRequested())
        {
            stateStack.pop();
            if (!stateStack.empty())
            {
                stateStack.top()->Resume();
            }
        }
        if (storedState)
        {
            if (!stateStack.empty())
            {
                stateStack.top()->Pause();
            }
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(dt);
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(2);
    }
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearImages();
}
