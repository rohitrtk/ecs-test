#include "CollisionSystem.h"
#include "GameObject.h"
#include "Game.h"

void CollisionSystem::update(ComponentManager& manager, float deltaTime) {
	static unsigned int x = 0;

	Game& game = Game::getInstance();

	for (auto& [e1, box1] : manager.collisions) {
		for (auto& [e2, box2] : manager.collisions) {
			if (e1 != e2 && checkCollision(box1, box2)) {
				GameObject* o1;
				GameObject* o2;

				if (o1) o1->onCollide(*o2);
				if (o2) o2->onCollide(*o1);
			}
		}
	}

	for (int e = 1; e <= manager.getTotalEntities(); e++) {
		if (
			manager.collisions.contains(e) &&
			manager.transforms.contains(e) &&
			manager.keys.contains(e)
			) {
			manager.collisions[e].position = manager.transforms[e].position;

			for (int e2 = 1; e2 <= manager.getTotalEntities(); e2++) {
				if (
					e != e2 &&
					manager.collisions.contains(e2) &&
					checkCollision(manager.collisions[e], manager.collisions[e2])
					) {
					printf("COLLIDE %d\n", x);
					x++;

					manager.transforms[e].position = manager.transforms[e].previousPosition;
				}
			}
		}
	}
}

void CollisionSystem::render(ComponentManager& manager, SDL_Renderer* renderer) {
	for (int e = 1; e <= manager.getTotalEntities(); e++) {
		if (manager.collisions.contains(e)) {
			vec2& position = manager.collisions[e].position;
			vec2& size = manager.collisions[e].size;

			/* Debug outline */
			if (mShowOutline) {
				SDL_Rect outline = { position.x, position.y, size.x, size.y };
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(renderer, &outline);
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
}

bool CollisionSystem::checkCollision(BoxCollisionComponent& a, BoxCollisionComponent& b) {
	if (
		isColliding(a, b, BoxCollisionComponent::Left) ||
		isColliding(a, b, BoxCollisionComponent::Right) ||
		isColliding(a, b, BoxCollisionComponent::Up) ||
		isColliding(a, b, BoxCollisionComponent::Down)
		) {
		return true;
	}

	return false;
}

bool CollisionSystem::isColliding(const BoxCollisionComponent& a, const BoxCollisionComponent& b, int collisionSide) {
	switch (collisionSide) {
	case BoxCollisionComponent::Left:
		return (a.position.x < b.position.x + b.size.x &&
			a.position.x + a.size.x > b.position.x &&
			a.position.y < b.position.y + b.size.y &&
			a.position.y + a.size.y > b.position.y &&
			(a.enabledCollisions & BoxCollisionComponent::Left) &&
			(b.enabledCollisions & BoxCollisionComponent::Right));
	case BoxCollisionComponent::Right:
		return (a.position.x + a.size.x > b.position.x &&
			a.position.x < b.position.x + b.size.x &&
			a.position.y < b.position.y + b.size.y &&
			a.position.y + a.size.y > b.position.y &&
			(a.enabledCollisions & BoxCollisionComponent::Right) &&
			(b.enabledCollisions & BoxCollisionComponent::Left));
	case BoxCollisionComponent::Up:
		return (a.position.y < b.position.y + b.size.y &&
			a.position.y + a.size.y > b.position.y &&
			a.position.x < b.position.x + b.size.x &&
			a.position.x + a.size.x > b.position.x &&
			(a.enabledCollisions & BoxCollisionComponent::Up) &&
			(b.enabledCollisions & BoxCollisionComponent::Down));
	case BoxCollisionComponent::Down:
		return (a.position.y + a.size.y > b.position.y &&
			a.position.y < b.position.y + b.size.y &&
			a.position.x < b.position.x + b.size.x &&
			a.position.x + a.size.x > b.position.x &&
			(a.enabledCollisions & BoxCollisionComponent::Down) &&
			(b.enabledCollisions & BoxCollisionComponent::Up));
	default:
		return false;
	}
}

void CollisionSystem::setShowOutline(bool showOutline) {
	mShowOutline = showOutline;
}

bool CollisionSystem::getShowOutline() const {
	return mShowOutline;
}