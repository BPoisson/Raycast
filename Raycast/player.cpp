#include "player.h"

Player::Player() : xDir(0), yDir(0), speed(0.02f), rect(SDL_FRect{ 250, 250, 25, 25 }), color(SDL_Color{ 255, 255, 255, 255 }) {}

void Player::Move() {
	rect.x += (xDir * speed);
	rect.y += (yDir * speed);
}

void Player::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}