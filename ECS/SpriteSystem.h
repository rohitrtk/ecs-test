#pragma once

#include "ComponentManager.h"

struct SpriteSystem {
	void update(ComponentManager& manager);
	void render(ComponentManager& manager, SDL_Renderer* renderer);
};