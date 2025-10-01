#ifndef PLAYER_H
#define PLAYER_H

#include "ray.h"
#include "renderable.h"
#include <vector>
#include <SDL3/SDL.h>

struct CollisionResult {
	bool isColliding = false;
	float x = 0.0;
	float y = 0.0;
};

class Player : public Renderable {
public:
	Player();
	~Player() = default;
	int xDir = 0;
	int yDir = 0;
	int rayDir = 0;
	float angle = 0.0f;
	const float rectDimension = 25.0f;
	SDL_FRect rect{ 250, 250, rectDimension, rectDimension };
	SDL_Color color{ 255, 255, 255, 255 };
	std::vector<Ray> rays;

	void Init(int screenWidth);
	void Update(float deltaTime, std::vector<Obstacle*> obstacles);
	void Render(SDL_Renderer* renderer) const override;

private:
	float speed = 250.0f;

	void Move(float deltaTime, std::vector<Obstacle*> obstacles);
	CollisionResult CheckCollision(float nextX, float nextY, std::vector<Obstacle*> obstacles);
	CollisionResult isColliding(float nextX, float nextY, Obstacle* obstacle);
	void UpdateRayAngle(float deltaTime);
	void UpdateRays();
	void Clean();
};

#endif