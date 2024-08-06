#pragma once

#include "GameObject.h"

namespace TileTypes {
	constexpr char NONE				= 0x0;
	constexpr char WATER_1			= 0x3;
	constexpr char WATER_2			= 0x4;
	constexpr char GRASS_TL_WATER	= 0xC;
	constexpr char GRASS_TM_WATER	= 0xD;
	constexpr char GRASS_TR_WATER	= 0xE;
	constexpr char GRASS_ML_WATER	= 0x11;
	constexpr char GRASS			= 0x12;
	constexpr char GRASS_MR_WATER	= 0x13;
	constexpr char GRASS_BL_WATER	= 0x16;
	constexpr char GRASS_BM_WATER	= 0x17;
	constexpr char GRASS_BR_WATER	= 0x18;
}

struct SDL_Texture;

class Tile : public GameObject {
public:
	Tile(float x, float y);
	Tile(SDL_Texture* spritesheet, float x, float y, int type);
	~Tile();

	virtual void start();
	virtual void update(float deltaTime);
};

