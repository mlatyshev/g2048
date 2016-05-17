#pragma once

#include <SDL.h>

class Entity {
public:
	Entity(SDL_Renderer* renderer);
	virtual ~Entity();

	float x, y, width, height;

	virtual void Update();
	virtual void Render();
protected:
	SDL_Renderer* renderer;
};