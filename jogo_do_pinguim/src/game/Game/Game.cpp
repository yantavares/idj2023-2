#include "Game.hpp"
#include "../InputManager/InputManager.hpp"
#include "../StageState/StageState.hpp"

Game *Game::instance = nullptr;

Game::Game(string title, int width, int height): storedState(nullptr)
{
    if (instance != nullptr)
    {
        cerr << "Error: Only one instance of Game is allowed." << endl;
        exit(1);
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
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

    frameStart = 0;
    dt = 0.0f;
}

int Game::GetWidth()
{
    return width;
}

int Game::GetHeight()
{
    return height;
}

Game &Game::GetInstance()
{

    if (instance == nullptr)
    {
        instance = new Game("Yan Tavares, 202041323 :)", 1024, 600);
        instance->width = 1024;
        instance->height = 600;
    }
    return *instance;
}

Game::~Game()
{
    delete &storedState;

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

State &Game::GetCurrentState()
{

    return *storedState;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
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
    InputManager &input = InputManager::GetInstance();
    storedState = new StageState();
    storedState->Start();
    while (!storedState->QuitRequested())
    {
        CalculateDeltaTime();
        storedState->Render();
        SDL_RenderPresent(Game::GetInstance().GetRenderer());
        input.Update();
        storedState->Update(GetDeltaTime());
    }
}

void Game::Push(State* state) {
    storedState = state;
}

void Game::Run() {
    if (storedState != nullptr) {
        stateStack.push_back(std::shared_ptr<State>(storedState));
        stateStack.back()->Start();
        storedState = nullptr;
    } else {
        // Encerrar o jogo se não houver estado inicial
        return;
    }

    while (!stateStack.empty()) {
        if (stateStack.back()->QuitRequested()) {
            break;
        }

        if (stateStack.back()->PopRequested()) {
            stateStack.pop_back();
            if (!stateStack.empty()) {
                stateStack.back()->Resume();
            }
        }

        if (storedState != nullptr) {
            stateStack.back()->Pause();
            stateStack.push_back(std::shared_ptr<State>(storedState));
            stateStack.back()->Start();
            storedState = nullptr;
        }

        // Aqui, execute Update e Render para o estado atual
        stateStack.back()->Update(dt);
        stateStack.back()->Render();
    }

    // Limpeza dos recursos ao sair do jogo
}
