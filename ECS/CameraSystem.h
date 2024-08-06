#pragma once

#include "ComponentManager.h"

struct CameraSystem {
	void update(ComponentManager& manager, float deltaTime);
};