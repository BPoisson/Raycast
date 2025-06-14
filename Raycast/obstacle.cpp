#include "obstacle.h"

Obstacle::Obstacle(SDL_FRect rect) : rect(rect) {}

void Obstacle::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}