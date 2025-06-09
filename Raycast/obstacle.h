#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "renderable.h"

class Obstacle : public Renderable {
public:
	Obstacle(SDL_FRect rect);
	~Obstacle() = default;

	SDL_FRect rect;
	SDL_Color color = SDL_Color { 255, 255, 255, 255 };

	void Render(SDL_Renderer* renderer) const override;
};

#endif