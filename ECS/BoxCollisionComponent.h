#pragma once

#include "Helpers.h"

struct BoxCollisionComponent {
	vec2 position = { 0, 0 };
	vec2 size = { 0,0 };

	enum Collisions {
		None = 0,
		Left = 1 << 0,
		Right = 1 << 1,
		Up = 1 << 2,
		Down = 1 << 3
	};

	int enabledCollisions =
		Collisions::Left |
		Collisions::Right |
		Collisions::Up |
		Collisions::Down;
};