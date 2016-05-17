#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer) {
	this->renderer = renderer;

	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

Entity::~Entity() {
}

void Entity::Update() {
}

void Entity::Render() {
}