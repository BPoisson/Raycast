#include "game.h"
#include <iostream>

Game::Game() : isRunning(false) {};

Game::~Game() {
    Clean();
}

bool Game::Init(const char* title, int width, int height) {
    engine = Engine();

    if (!engine.Init(title, width, height)) {
        return false;
    }
    player = new Player();
    isRunning = true;
    renderables.insert(player);
    return true;
}

void Game::Run() {
    while (isRunning) {
        engine.Update();
        Update();
    }
    Clean();
}

void Game::Update() {
    HandleInput();
    player->Move();
    engine.Render(renderables);
}

void Game::HandleInput() {
    HandleMouseInput();
    HandleKeyboardInput();
}

void Game::HandleMouseInput() {
    if (engine.GetLeftMouseButtonDown()) {
        if (!engine.GetLeftPrevMouseButtonDown()) {
            // Starting a new box.
            float x = engine.GetMouseX();
            float y = engine.GetMouseY();
            SDL_FRect rect;

            rect.x = x;
            rect.y = y;
            rect.w = 0;
            rect.h = 0;

            Obstacle* obstacle = new Obstacle(rect);
            obstacles.push_back(obstacle);
            renderables.insert(obstacle);
        } else if (!obstacles.empty()) {
            // Resizing an existing box.
            float x = engine.GetMouseX();
            float y = engine.GetMouseY();
            
            SDL_FRect* rect = &obstacles.back()->rect;
            rect->w = x - rect->x;
            rect->h = y - rect->y;
        }
    }
    if (engine.GetRightMouseButtonDown()) {
        if (!engine.GetRightPrevMouseButtonDown()) {
            float mouseX = engine.GetMouseX();
            float mouseY = engine.GetMouseY();

            for (int i = static_cast<int>(obstacles.size()) - 1; i >= 0; i--) {
                SDL_FRect rect = obstacles.at(i)->rect;
                float rectStartX = rect.w >= 0 ? rect.x : rect.x + rect.w;
                float rectStartY = rect.h >= 0 ? rect.y : rect.y + rect.h;
                float rectEndX = rect.w >= 0 ? rect.x + rect.w : rect.x;
                float rectEndY = rect.h >= 0 ? rect.y + rect.h : rect.y;

                if (rectStartX <= mouseX && mouseX <= rectEndX && rectStartY <= mouseY && mouseY <= rectEndY) {
                    renderables.erase(obstacles[i]);
                    delete obstacles[i];
                    obstacles.erase(obstacles.begin() + i);
                    break;
                }
            }
        }
    }
}

void Game::HandleKeyboardInput() {
    if (engine.GetQuitRequested()) {
        isRunning = false;
    }

    if (engine.GetWKeyDown()) {
        player->yDir = -1;
    } else if (engine.GetSKeyDown()) {
        player->yDir = 1;
    } else {
        player->yDir = 0;
    }

    if (engine.GetAKeyDown()) {
        player->xDir = -1;
    } else if (engine.GetDKeyDown()) {
        player->xDir = 1;
    } else {
        player->xDir = 0;
    }
}

void Game::Clean() {
    engine.Quit();
}