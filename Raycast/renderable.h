#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SDL3/SDL.h>

class Renderable {
public:
	virtual ~Renderable() = default;
	
	virtual void Render(SDL_Renderer* renderer) const = 0;
};

#endif