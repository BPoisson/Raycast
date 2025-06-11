#include "player.h"
#include <iostream>

Player::Player() {}

void Player::Init(int screenWidth) {
	float startX = this->rect.x + this->rectDimension;
	float startY = this->rect.y + this->rectDimension / 2;

	for (int i = 0; i < screenWidth; i++) {
		rays.push_back(Ray(startX, startY, 0.0f));
	}
}

void Player::Update(float deltaTime) {
	Move(deltaTime);
	UpdateRays();	
}

void Player::UpdateRays() {
	constexpr float PI = 3.14159265f;
	float fieldOfView = 90.0f * (PI / 180.0f);
	float startX = this->rect.x + this->rectDimension;
	float startY = this->rect.y + this->rectDimension / 2;

	for (int i = 0; i < rays.size(); i++) {
		Ray* ray = &rays.at(i);

		float rayAngle = this->angle - (fieldOfView / 2.0f) + (static_cast<float>(i) / static_cast<float>(rays.size())) * fieldOfView;
		ray->UpdatePosition(startX, startY, rayAngle);
	}
}

void Player::Move(float deltaTime) {
	rect.x += (xDir * speed * deltaTime);
	rect.y += (yDir * speed * deltaTime);
}

void Player::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::Clean() {

}