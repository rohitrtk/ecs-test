#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>

struct Animation {
	std::vector<int> frames;
	float frameTime;
	bool loop;
};

struct SpriteSheetComponent {
	SDL_Texture* texture;

	int spriteWidth;
	int spriteHeight;
	int numRows;
	int numCols;

	std::unordered_map<std::string, Animation> animations;
	std::string currentAnimation;
	int currentFrame;
	float elapsedTime;
};