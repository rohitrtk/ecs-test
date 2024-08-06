#pragma once

#include "Helpers.h"

struct TransformComponent {
	vec2 position = { 0, 0 };
	vec2 velocity = { 0, 0 };

	vec2 previousPosition = { 0,0 };

	float movementSpeed = 500.f;

	enum Direction {
		None,
		Right,
		Left,
		Up,
		Down
	};

	Direction movementDirection = None;
};