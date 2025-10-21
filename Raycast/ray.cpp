#include "ray.h"
#include "constants.h"
#include <cmath>
#include <iostream>

constexpr float maxRayLen = 500.0f;

Ray::Ray(int rayNum, float startX, float startY, float angle) {
	this->rayNum = rayNum;
	this->wallX = (SCREEN_WIDTH / 2) + rayNum;
	UpdatePosition(startX, startY, angle);
}

void Ray::Update(std::vector<Obstacle*> obstacles) {
	CheckCollision(obstacles);
}

void Ray::UpdatePosition(float playerX, float playerY, float playerAngle) {
	this->x1 = playerX;
	this->y1 = playerY;
	this->angle = playerAngle;
	this->x2 = playerX + maxRayLen * cos(angle);
	this->y2 = playerY + maxRayLen * sin(angle);
}

void Ray::CheckCollision(std::vector<Obstacle*> obstacles) {
	this->intersecting = false;

	for (Obstacle* obstacle : obstacles) {
		Vector4 obstacleTopLine = Vector4{ obstacle->rect.x, obstacle->rect.y, obstacle->rect.x + obstacle->rect.w, obstacle->rect.y };
		Vector4 obstacleBotLine = Vector4{ obstacle->rect.x, obstacle->rect.y + obstacle->rect.h, obstacle->rect.x + obstacle->rect.w, obstacle->rect.y + obstacle->rect.h };
		Vector4 obstacleLeftLine = Vector4{ obstacle->rect.x, obstacle->rect.y, obstacle->rect.x, obstacle->rect.y + obstacle->rect.h };
		Vector4 obstacleRightLine = Vector4{ obstacle->rect.x + obstacle->rect.w, obstacle->rect.y, obstacle->rect.x + obstacle->rect.w, obstacle->rect.y + obstacle->rect.h };

		CheckIntersection(obstacleTopLine);
		CheckIntersection(obstacleBotLine);
		CheckIntersection(obstacleLeftLine);
		CheckIntersection(obstacleRightLine);
	}
}

// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
void Ray::CheckIntersection(Vector4 wall) {
	float dxRay = x2 - x1;
	float dyRay = y2 - y1;
	float dxWall = wall.x2 - wall.x1;
	float dyWall = wall.y2 - wall.y1;

	float denominator = dxRay * dyWall - dyRay * dxWall;

	// Parallel or coincident lines.
	if (denominator == 0.0f) {
		return;
	}

	float sx = wall.x1 - x1;
	float sy = wall.y1 - y1;

	// How far along the ray we travel.
	float t = (sx * dyWall - sy * dxWall) / denominator;
	// How far along the wall segment we travel.
	float u = (sx * dyRay - sy * dxRay) / denominator;

	if (t >= 0.0f && u >= 0.0f && u <= 1.0f) {
		float xIntersect = x1 + t * dxRay;
		float yIntersect = y1 + t * dyRay;

		float currDist = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
		float newDist = (xIntersect - x1) * (xIntersect - x1) + (yIntersect - y1) * (yIntersect - y1);

		if (newDist < currDist) {
			this->intersecting = true;
			this->x2 = xIntersect;
			this->y2 = yIntersect;
			this->intersectDist = newDist;
		}
	}
}

void Ray::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_SetRenderColorScale(renderer, 1.0f);
	SDL_RenderLine(renderer, x1, y1, x2, y2);

	// Ray has intersected an obstacle. Draw wall.
	if (this->intersecting) {
		float maxX = this->x1 + maxRayLen * cos(this->angle);
		float maxY = this->y1 + maxRayLen * sin(this->angle);
		float maxDist = (maxX - this->x1) * (maxX - this->x1) + (maxY - this->y1) * (maxY - this->y1);
		float distRatio = (this->intersectDist / maxDist);
		float heightDiff = (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 2) * distRatio;
		float wallY1 = (SCREEN_HEIGHT / 2) - heightDiff;
		float wallY2 = (SCREEN_HEIGHT / 2) + heightDiff;

		SDL_SetRenderDrawColor(renderer, wallColor.r, wallColor.g, wallColor.b, wallColor.a);
		SDL_SetRenderColorScale(renderer, 1.0f - distRatio);
		SDL_RenderLine(renderer, wallX, wallY1, wallX, wallY2);
	}
}