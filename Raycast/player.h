#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "renderable.h"

class Player : public Renderable {
public:
	Player();
	~Player() = default;

	int xDir;
	int yDir;
	SDL_FRect rect;
	SDL_Color color;

	void Move();
	void Render(SDL_Renderer* renderer) const override;

private:
	float speed;
};

#endif