#pragma once

#include "ComponentManager.h"

struct CollisionSystem {
	void update(ComponentManager& manager, float deltaTime);
	void render(ComponentManager& manager, SDL_Renderer* renderer);

	bool checkCollision(BoxCollisionComponent& a, BoxCollisionComponent& b);
	bool isColliding(const BoxCollisionComponent& a, const BoxCollisionComponent& b, int collisionSide);

	void setShowOutline(bool showOutline);
	bool getShowOutline() const;

private:
	bool mShowOutline = false;
};