#ifndef ENGINE_H
#define ENGINE_H

#include "inputHandler.h"
#include <SDL3/SDL.h>
#include <vector>

class Engine {
public:
	Engine();
	~Engine();

	std::vector<SDL_FRect> rects;

	bool Init(const char* title, int width, int height);
	void Run();
	void Clean();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	InputHandler* inputHandler;
	

	void HandleInput();
	void Update();
	void Render();
};

#endif