#pragma once

#include <SDL.h>

struct SpriteComponent {
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Texture* texture;

	int spriteIndex = -1;
};