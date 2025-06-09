#include "game.h"

Game::Game() : isRunning(false) {};

Game::~Game() {
    Clean();
}

bool Game::Init(const char* title, int width, int height) {
    engine = Engine();

    if (!engine.Init(title, width, height)) {
        return false;
    }
    isRunning = true;
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
    engine.Render(obstacles);
}

void Game::HandleInput() {
    if (engine.GetQuitRequested()) {
        isRunning = false;
    }

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

            obstacles.push_back(new Obstacle(rect));
        } else if (!obstacles.empty()) {
            // Resizing an existing box.
            float x = engine.GetMouseX();
            float y = engine.GetMouseY();
            SDL_FRect* rect = &static_cast<Obstacle*>(obstacles.back())->rect;

            rect->w = x - rect->x;
            rect->h = y - rect->y;
        }
    }
    if (engine.GetRightMouseButtonDown()) {
        if (!engine.GetRightPrevMouseButtonDown()) {
            float mouseX = engine.GetMouseX();
            float mouseY = engine.GetMouseY();

            for (int i = static_cast<int>(obstacles.size()) - 1; i >= 0; i--) {
                SDL_FRect rect = static_cast<Obstacle*>(obstacles.at(i))->rect;
                float rectStartX = rect.w >= 0 ? rect.x : rect.x + rect.w;
                float rectStartY = rect.h >= 0 ? rect.y : rect.y + rect.h;
                float rectEndX = rect.w >= 0 ? rect.x + rect.w : rect.x;
                float rectEndY = rect.h >= 0 ? rect.y + rect.h : rect.y;

                if (rectStartX <= mouseX && mouseX <= rectEndX && rectStartY <= mouseY && mouseY <= rectEndY) {
                    delete obstacles[i];
                    obstacles.erase(obstacles.begin() + i);
                    break;
                }
            }
        }
    }
}

void Game::Clean() {
    engine.Quit();
}