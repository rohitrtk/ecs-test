#pragma once

#include "ComponentManager.h"

struct TransformSystem {
	void update(ComponentManager& manager, float deltaTime);
};