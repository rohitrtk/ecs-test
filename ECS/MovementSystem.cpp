#include "MovementSystem.h"

void MovementSystem::update(ComponentManager& manager) {
	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	for (int e = 1; e <= manager.getTotalEntities(); e++) {
		if (manager.transforms.contains(e) && manager.keys.contains(e)) {
			if (keys[SDL_SCANCODE_A]) manager.transforms[e].velocity.x = -1.0f;
			if (keys[SDL_SCANCODE_S]) manager.transforms[e].velocity.y = 1.0f;
			if (keys[SDL_SCANCODE_W]) manager.transforms[e].velocity.y = -1.0f;
			if (keys[SDL_SCANCODE_D]) manager.transforms[e].velocity.x = 1.0f;

			if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) manager.transforms[e].velocity.x = 0.0f;
			if (!keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) manager.transforms[e].velocity.y = 0.0f;
		}
	}
}