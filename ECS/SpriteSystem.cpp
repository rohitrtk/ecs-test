#include "SpriteSystem.h"

#include <SDL.h>
#include <SDL_image.h>

void SpriteSystem::update(ComponentManager& manager) {
	for (int e = 1; e <= manager.getTotalEntities(); e++) {
		if (manager.sprites.contains(e) && manager.transforms.contains(e)) {
			manager.sprites[e].dst.x = manager.transforms[e].position.x;
			manager.sprites[e].dst.y = manager.transforms[e].position.y;
		}
	}
}

void SpriteSystem::render(ComponentManager& manager, SDL_Renderer* renderer) {
	auto& camera = getCamera(manager);
	//std::printf("Camera Position: (%f, %f)\n", camera.position.x, camera.position.y);

	for (int e = 1; e <= manager.getTotalEntities(); e++) {
		if (manager.sprites.contains(e)) {
			auto& sprite = manager.sprites[e];

			if (manager.spriteSheets.contains(e)) {
				auto& spriteSheet = manager.spriteSheets[e];

				if (!spriteSheet.currentAnimation.empty()) {
					auto& anim = spriteSheet.animations[spriteSheet.currentAnimation];
					int frameIndex = anim.frames[spriteSheet.currentFrame];
					int row = frameIndex / spriteSheet.numCols;
					int col = frameIndex % spriteSheet.numCols;

					SDL_Rect srcRect = {
						col * spriteSheet.spriteWidth,
						row * spriteSheet.spriteHeight,
						spriteSheet.spriteWidth,
						spriteSheet.spriteHeight
					};

					sprite.src = srcRect;
				}

				SDL_Rect adjustedDst = sprite.dst;
				adjustedDst.x = sprite.dst.x - camera.position.x;
				adjustedDst.y = sprite.dst.y - camera.position.y;
				adjustedDst.w *= camera.zoom;
				adjustedDst.h *= camera.zoom;
				
				//SDL_RenderCopy(renderer, spriteSheet.texture, &sprite.src, &sprite.dst);
				SDL_RenderCopy(renderer, spriteSheet.texture, &sprite.src, &adjustedDst);
			}
			else {
				SDL_Rect adjustedDst = sprite.dst;
				adjustedDst.x = sprite.dst.x - camera.position.x;
				adjustedDst.y = sprite.dst.y - camera.position.y;

				//SDL_RenderCopy(renderer, sprite.texture, &sprite.src, &sprite.dst);
				SDL_RenderCopy(renderer, sprite.texture, &sprite.src, &adjustedDst);
			}
		}
	}
}