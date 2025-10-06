#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_set>
#include "engine.h"
#include "player.h"
#include "obstacle.h"

class Game {
public:
	Game();
	~Game();

	int screenWidth = 0;
	int screenHeight = 0;
	bool isRunning = false;
	Player player;
	std::vector<Obstacle*> obstacles;
	std::unordered_set<Renderable*> renderables;	// We might care about render order later. Switch to ECS?

	bool Init(const char* title, int width, int height);
	void Run();

private:
	Engine engine;

	void Update(float deltaTime);
	void HandleInput();
	void HandleMouseInput();
	void HandleKeyboardInput();
	void Clean();
};

#endif