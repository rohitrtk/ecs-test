#include "AnimationSystem.h"

void AnimationSystem::update(ComponentManager& manager, float deltaTime) {
	for (auto& [entity, spriteSheet] : manager.spriteSheets) {
		if (!spriteSheet.currentAnimation.empty()) {

			//auto& transform = manager.transforms[entity];
			auto& transform = manager.getComponent<TransformComponent>(entity);
			bool isMoving = transform.velocity.x != 0 || transform.velocity.y != 0;

			if (isMoving) {
				spriteSheet.currentAnimation = "walk";
				auto& anim = spriteSheet.animations[spriteSheet.currentAnimation];
				spriteSheet.elapsedTime += deltaTime;

				if (spriteSheet.elapsedTime >= anim.frameTime) {
					spriteSheet.elapsedTime = 0.0f;
					spriteSheet.currentFrame++;

					if (spriteSheet.currentFrame >= anim.frames.size()) {
						if (anim.loop) {
							spriteSheet.currentFrame = 0;
						}
						else {
							spriteSheet.currentFrame = anim.frames.size() - 1;
						}
					}
				}
			}
			else {
				spriteSheet.currentAnimation = "idle";
				spriteSheet.currentFrame = 0;
				spriteSheet.elapsedTime = 0.0f;
			}

		}
	}
}