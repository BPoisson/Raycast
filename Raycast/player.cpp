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

void Player::Update(float deltaTime, std::vector<Obstacle*> obstacles) {
	Move(deltaTime, obstacles);
	UpdateRayAngle(deltaTime);
	UpdateRays();	
}

void Player::UpdateRays() {
	constexpr float PI = 3.14159265f;
	float fieldOfView = 90.0f * (PI / 180.0f);
	float startX = this->rect.x + this->rectDimension / 2;
	float startY = this->rect.y + this->rectDimension / 2;

	for (int i = 0; i < rays.size(); i++) {
		Ray* ray = &rays.at(i);

		float rayAngle = this->angle - (fieldOfView / 2.0f) + (static_cast<float>(i) / static_cast<float>(rays.size())) * fieldOfView;
		ray->UpdatePosition(startX, startY, rayAngle);
	}
}

void Player::Move(float deltaTime, std::vector<Obstacle*> obstacles) {
	float nextX = this->rect.x + xDir * speed * deltaTime;
	float nextY = this->rect.y + yDir * speed * deltaTime;

	CollisionResult collisionResult = CheckCollision(nextX, nextY, obstacles);

	if (!collisionResult.isColliding) {
		this->rect.x = nextX;
		this->rect.y = nextY;
	} else {
		this->rect.x = collisionResult.x;
		this->rect.y = collisionResult.y;
	}
}

CollisionResult Player::CheckCollision(float nextX, float nextY, std::vector<Obstacle*> obstacles) {
	for (Obstacle* obstacle : obstacles) {
		CollisionResult collisionResult = isColliding(nextX, nextY, obstacle);

		if (collisionResult.isColliding) {
			return collisionResult;
		}
	}
	return CollisionResult();
}

// TODO: Handle issues in diagonal movement between two nearby obstacles, allowing the player to pass through.
CollisionResult Player::isColliding(float nextX, float nextY, Obstacle* obstacle) {
	float playerXStart = nextX;
	float playerYStart = nextY;
	float playerXEnd = nextX + this->rect.w;
	float playerYEnd = nextY + this->rect.h;

	float obstacleXStart = obstacle->rect.x;
	float obstacleYStart = obstacle->rect.y;
	float obstacleXEnd = obstacleXStart + obstacle->rect.w;
	float obstacleYEnd = obstacleYStart + obstacle->rect.h;

	bool xCollision = playerXStart < obstacleXEnd && obstacleXStart < playerXEnd;
	bool yCollision = playerYStart < obstacleYEnd && obstacleYStart < playerYEnd;

	if (!xCollision || !yCollision) {
		return CollisionResult{};
	}

	float xOverlapLeft = playerXEnd - obstacleXStart;
	float xOverlapRight = obstacleXEnd - playerXStart;
	float yOverlapTop = playerYEnd - obstacleYStart;
	float yOverlapBot = obstacleYEnd - playerYStart;

	float minOverlapX = 0.0;
	if (xOverlapLeft < xOverlapRight) {
		minOverlapX = xOverlapLeft;
	} else {
		minOverlapX = -xOverlapRight;
	}

	float minOverlapY = 0.0;
	if (yOverlapTop < yOverlapBot) {
		minOverlapY = yOverlapTop;
	} else {
		minOverlapY = -yOverlapBot;
	}

	float xPos = nextX;
	float yPos = nextY;
	if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
		xPos = nextX - minOverlapX;
	} else {
		yPos = nextY - minOverlapY;
	}
	return CollisionResult { true, xPos, yPos };
}

void Player::UpdateRayAngle(float deltaTime) {
	this->angle += (rayDir * deltaTime);
}

void Player::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::Clean() {

}