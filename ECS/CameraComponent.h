#pragma once

#include <SDL.h>
#include "Helpers.h"

struct CameraComponent {
	vec2 position = { 0, 0 };
	float zoom = 1.0f;
};