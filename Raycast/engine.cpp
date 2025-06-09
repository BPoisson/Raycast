#include "engine.h"
#include <iostream>

Engine::Engine() : isRunning(false), window(nullptr), renderer(nullptr), inputHandler(nullptr) {}

Engine::~Engine() {
	Clean();
}

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

void Engine::Update() {
    inputHandler->HandleEvents();
}

void Engine::Render(std::unordered_set<Renderable*>& renderables) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const auto& renderable : renderables) {
        renderable->Render(renderer);
    }

    SDL_RenderPresent(renderer);
}

bool Engine::GetQuitRequested() const {
    return inputHandler->GetQuitRequested();
}

bool Engine::GetLeftMouseButtonDown() const {
    return inputHandler->GetLeftMouseButtonDown();
}

bool Engine::GetRightMouseButtonDown() const {
    return inputHandler->GetRightMouseButtonDown();
}

bool Engine::GetLeftPrevMouseButtonDown() const {
    return inputHandler->GetLeftPrevMouseButtonDown();
}

bool Engine::GetRightPrevMouseButtonDown() const {
    return inputHandler->GetRightPrevMouseButtonDown();
}

float Engine::GetMouseX() const {
    return inputHandler->GetMouseX();
}

float Engine::GetMouseY() const {
    return inputHandler->GetMouseY();
}

bool Engine::GetWKeyDown() {
    return inputHandler->GetWKeyDown();
}

bool Engine::GetAKeyDown() {
    return inputHandler->GetAKeyDown();
}

bool Engine::GetSKeyDown() {
    return inputHandler->GetSKeyDown();
}

bool Engine::GetDKeyDown() {
    return inputHandler->GetDKeyDown();
}

bool Engine::GetUpKeyDown() {
    return inputHandler->GetUpKeyDown();
}

bool Engine::GetDownKeyDown() {
    return inputHandler->GetDownKeyDown();
}

bool Engine::GetLeftKeyDown() {
    return inputHandler->GetLeftKeyDown();
}

bool Engine::GetRightKeyDown() {
    return inputHandler->GetRightKeyDown();
}

void Engine::Quit() {
    isRunning = false;
    Clean();
}

void Engine::Clean() {
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
}