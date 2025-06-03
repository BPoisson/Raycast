#include "engine.h"
#include <iostream>

Engine::Engine() : isRunning(false), window(nullptr), renderer(nullptr), inputHandler(nullptr) {}

Engine::~Engine() {
	Clean();
}

bool prevFrameMouseDown = false;

bool Engine::Init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    isRunning = true;
    inputHandler = new InputHandler();
    return true;
}

void Engine::Run() {
    while (isRunning) {
        inputHandler->HandleEvents();
        Update();
        Render();
    }
}

void Engine::Update() {
    HandleInput();
}

void Engine::HandleInput() {
    if (inputHandler->GetQuitRequested()) {
        isRunning = false;
        return;
    }
    
    if (inputHandler->GetMouseButtonDown()) {
        if (!inputHandler->GetPrevMouseButtonDown()) {
            // Starting a new box.
            float x = inputHandler->GetMouseState().x;
            float y = inputHandler->GetMouseState().y;
            SDL_FRect rect;

            rect.x = x;
            rect.y = y;
            rect.w = 0;
            rect.h = 0;

            rects.push_back(rect);
            prevFrameMouseDown = true;
        } else if (!rects.empty()) {
            // Resizing an existing box.
            float x = inputHandler->GetMouseState().x;
            float y = inputHandler->GetMouseState().y;
            SDL_FRect* rect = &rects.at(rects.size() - 1);

            rect->w = x - rect->x;
            rect->h = y - rect->y;
            prevFrameMouseDown = true;
        }
    }
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (SDL_FRect rect : rects) {
        SDL_RenderRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void Engine::Clean() {
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
}