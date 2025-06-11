#ifndef RAY_H
#define RAY_H

#include "renderable.h"
#include <SDL3/SDL.h>

class Ray : public Renderable {
public:
	Ray(float startX, float startY, float angle);
	~Ray() = default;

	float startX;
	float startY;
	float endX;
	float endY;
	float angle;
	SDL_Color color{ 128, 128, 128, 255 };

	void UpdatePosition(float startX, float startY, float angle);
	void Render(SDL_Renderer* renderer) const override;
private:
};

#endif