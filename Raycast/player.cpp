#include "player.h"

Player::Player() : xDir(0), yDir(0), speed(250.0f), rect(SDL_FRect{ 250, 250, 25, 25 }), color(SDL_Color{ 255, 255, 255, 255 }) {}

void Player::Move(float deltaTime) {
	rect.x += (xDir * speed * deltaTime);
	rect.y += (yDir * speed * deltaTime);
}

void Player::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}