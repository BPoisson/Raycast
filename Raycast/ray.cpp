#include "ray.h"
#include <cmath>
#include <iostream>

Ray::Ray(float startX, float startY, float angle) {
	UpdatePosition(startX, startY, angle);
}

void Ray::UpdatePosition(float startX, float startY, float angle) {
	this->startX = startX;
	this->startY = startY;
	this->angle = angle;
	this->endX = startX + 100.0f * cos(angle);
	this->endY = startY + 100.0f * sin(angle);
}

void Ray::Render(SDL_Renderer* renderer) const {
	if (startX == endX && startY == endY) {
		return;
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderLine(renderer, startX, startY, endX, endY);
}