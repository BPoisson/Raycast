#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <vector>
#include "inputHandler.h"
#include "renderable.h"

class Engine {
public:
	Engine();
	~Engine();

	bool Init(const char* title, int width, int height);

	void Update();
	void Render(std::vector<Renderable*>& renderables);

	bool GetQuitRequested() const;
	bool GetLeftMouseButtonDown() const;
	bool GetRightMouseButtonDown() const;
	bool GetLeftPrevMouseButtonDown() const;
	bool GetRightPrevMouseButtonDown() const;
	float GetMouseX() const;
	float GetMouseY() const;

	void Quit();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	InputHandler* inputHandler;

	void HandleInput();
	void Clean();
};

#endif