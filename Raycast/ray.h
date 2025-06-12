#ifndef RAY_H
#define RAY_H

#include "renderable.h"
#include "obstacle.h"
#include "dataStructures.h"
#include <SDL3/SDL.h>
#include <vector>

class Ray : public Renderable {
public:
	Ray(float startX, float startY, float angle);
	~Ray() = default;

	float x1;
	float y1;
	float x2;
	float y2;
	float angle;
	SDL_Color color{ 128, 128, 128, 255 };

	void Update(std::vector<Obstacle*> obstacles);
	void UpdatePosition(float playerX, float playerY, float playerAngle);
	void CheckCollision(std::vector<Obstacle*> obstacles);
	void CheckIntersection(Vector4 wall);
	void Render(SDL_Renderer* renderer) const override;
private:
};

#endif