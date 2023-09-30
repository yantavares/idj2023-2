#include "State.hpp"
#include "../../components/Face/Face.hpp"
#include "../../geometry/Rect/Rect.hpp"
#include "../../geometry/Vec2/Vec2.hpp"
#include "../../components/Sound/Sound.hpp"
#include "../../components/TileMap/TileMap.hpp"
#include "../../components/TileSet/TileSet.hpp"
#include "../InputManager/InputManager.hpp"
#include "../Camera/Camera.hpp"
#include "../../components/CameraFollower/CameraFollower.hpp"

State::State()
{
    quitRequested = false;
    LoadAssets();
}

void State::LoadAssets()
{
    GameObject *background = new GameObject();
    Sprite *bg = new Sprite("../public/img/ocean.jpg", *background);
    background->box = {0, 0, bg->GetWidth(), bg->GetHeight()};
    background->AddComponent(bg);

    CameraFollower *cameraFollower = new CameraFollower(*background);
    background->AddComponent(cameraFollower);

    TileSet *tileSet = new TileSet(*background, 64, 64, "../public/img/tileset.png");
    TileMap *tileMap = new TileMap(*background, "../public/map/tileMap.txt", tileSet);

    background->AddComponent(tileMap);

    objectArray.emplace_back(background);

    music = new Music("../public/audio/stageState.ogg");
    music->Play();
}

bool State::QuitRequested()
{
    return quitRequested;
}

State::~State()
{
    objectArray.clear();
}

void State::Input()
{
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {

        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = objectArray.size() - 1; i >= 0; --i)
            {
                // Obtem o ponteiro e casta pra Face.
                GameObject *go = (GameObject *)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains({(float)mouseX, (float)mouseY}))
                {
                    Face *face = (Face *)go->GetComponent("Face");
                    if (nullptr != face)
                    {
                        // Aplica dano
                        face->Damage(rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else
            {
                Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::Update(float dt)
{
    SDL_Delay((int)dt);

    InputManager &input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested())
    {
        quitRequested = true;
    }

    if (input.KeyPress(SDLK_SPACE))
    {

        Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
        AddObject((int)objPos.x, (int)objPos.y);
    }

    for (unsigned int i = 0; i < objectArray.size(); i++)
    {

        if (objectArray[i]->IsDead())
        {

            objectArray.erase(objectArray.begin() + i);
            i--;
        }
        else
        {
            objectArray[i]->Update(dt);
        }
    }
    // Uptades Camera
    Camera::Update(dt);
}

void State::Render()
{
    for (int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

void State::AddObject(int x, int y)
{
    GameObject *go = new GameObject();
    Sprite *enemy = new Sprite("../public/img/penguinface.png", *go);

    go->box = {x, y, enemy->GetWidth(), enemy->GetHeight()};

    go->AddComponent(enemy);
    go->AddComponent(new Face(*go));
    go->AddComponent(new Sound(*go, "../public/audio/boom.wav"));
    objectArray.emplace_back(go);
}
