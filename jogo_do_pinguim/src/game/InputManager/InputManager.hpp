#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <bits/stdc++.h>

using namespace std;

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class InputManager
{
public:
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) = delete;

    static InputManager &GetInstance();

    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();

private:
    InputManager();
    ~InputManager();

    static constexpr int MOUSE_BUTTONS = 6;
    bool mouseState[MOUSE_BUTTONS];
    int mouseUpdate[MOUSE_BUTTONS];

    unordered_map<int, bool> keyState;
    unordered_map<int, int> keyUpdate;

    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
};

#endif
