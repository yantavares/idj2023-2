#include "Game.hpp"

Game *Game::instance = nullptr;

Game::Game(const string &title, int width, int height)
{
    if (instance != nullptr)
    {
        cerr << "Error: Only one instance of Game is allowed." << endl;
        exit(1);
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Error: Failed to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) & (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
    {
        cerr << "Error: Failed to initialize SDL_Image: " << IMG_GetError() << endl;
        exit(1);
    }

    if (Mix_Init(MIX_INIT_OGG) < 0)
    {
        cerr << "Error: Failed to initialize SDL_mixer: " << Mix_GetError() << endl;
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        cerr << "Error: Failed to open audio device: " << Mix_GetError() << endl;
        exit(1);
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        cerr << "Error: Failed to create SDL window: " << SDL_GetError() << endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cerr << "Error: Failed to create SDL renderer: " << SDL_GetError() << endl;
        exit(1);
    }
}

Game &Game::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Game("Yan Tavares, 202041323 :)", 1024, 600);
    }
    return *instance;
}

Game::~Game()
{
    delete &state;

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

State &Game::GetState()
{

    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

void Game::Run()
{
    while (state->QuitRequested())
    {
        state->Update(0.0);
        state->Render();
        if (renderer != nullptr)
        {
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(33);
    }
}