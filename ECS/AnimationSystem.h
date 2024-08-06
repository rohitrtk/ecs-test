#pragma once

#include "ComponentManager.h"

struct AnimationSystem {
	void update(ComponentManager& manager, float deltaTime);
};