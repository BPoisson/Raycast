#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include "engine.h"

class Game {
public:
	Game();
	~Game();

	bool isRunning;
	std::vector<SDL_FRect> obstacles;

	bool Init(const char* title, int width, int height);
	void Run();

private:
	Engine engine;

	void Update();
	void HandleInput();
	void Clean();
};

#endif