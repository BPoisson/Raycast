#include "game.h"
#include <iostream>

Game::Game() {}

Game::~Game() {
    Clean();
}

bool Game::Init(const char* title, int width, int height) {
    if (!engine.Init(title, width, height)) {
        return false;
    }
    player.Init(width);
    isRunning = true;
    renderables.insert(&player);
    
    for (Ray& ray : player.rays) {
        renderables.insert(&ray);
    }
    return true;
}

void Game::Run() {
    Uint64 lastTime = SDL_GetPerformanceCounter();
    float smoothedFPS = 0.0f;
    
    while (isRunning) {
        Uint64 currTime = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(currTime - lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
        lastTime = currTime;

        engine.Update();
        Update(deltaTime);

        float fps = 1.0f / deltaTime;
        smoothedFPS = 0.9f * smoothedFPS + 0.1f * fps;
        std::cout << "FPS: " << smoothedFPS << "\n";
    }
    Clean();
}

void Game::Update(float deltaTime) {
    HandleInput();
    player.Update(deltaTime, obstacles);
    for (Ray& ray : player.rays) {
        ray.Update(obstacles);
    }
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
        player.yDir = -1;
    } else if (engine.GetSKeyDown()) {
        player.yDir = 1;
    } else {
        player.yDir = 0;
    }

    if (engine.GetAKeyDown()) {
        player.xDir = -1;
    } else if (engine.GetDKeyDown()) {
        player.xDir = 1;
    } else {
        player.xDir = 0;
    }

    if (engine.GetLeftKeyDown()) {
        player.rayDir = -1;
    } else if (engine.GetRightKeyDown()) {
        player.rayDir = 1;
    } else {
        player.rayDir = 0;
    }
}

void Game::Clean() {
    for (Obstacle* obstacle : obstacles) {
        delete obstacle;
    }
    obstacles.clear();
    engine.Quit();
}