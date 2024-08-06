#include "TransformSystem.h"

void TransformSystem::update(ComponentManager& manager, float deltaTime) {
	for (int e = 1; e <= manager.getTotalEntities(); e++) {
		if (manager.transforms.contains(e)) {
			auto& transform = manager.transforms[e];

			transform.previousPosition = {
				transform.position.x,
				transform.position.y
			};
			transform.position.x += transform.velocity.x * deltaTime * transform.movementSpeed;
			transform.position.y += transform.velocity.y * deltaTime * transform.movementSpeed;

			if (transform.velocity.y < 0) transform.movementDirection = TransformComponent::Direction::Up;
			else if (transform.velocity.y > 0) transform.movementDirection = TransformComponent::Direction::Down;
			else if (transform.velocity.x > 0) transform.movementDirection = TransformComponent::Direction::Right;
			else if (transform.velocity.x < 0) transform.movementDirection = TransformComponent::Direction::Left;
		}
	}
}