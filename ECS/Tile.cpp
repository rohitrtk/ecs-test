#include "Tile.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

Tile::Tile(float x, float y) : GameObject() {
	Game& game = Game::getInstance();
	ComponentManager& manager = game.getComponentManager();

	this->addComponent<SpriteComponent>({
		SDL_Rect{0,0,302,403},
		SDL_Rect{0,0,48,48},
		IMG_LoadTexture(game.getRenderer(), "res/texture.png")
	});
	this->addComponent<TransformComponent>({x, y, 0, 0});
	this->addComponent<BoxCollisionComponent>({{x, y}, {48,48}});
}

Tile::Tile(SDL_Texture* spritesheet, float x, float y, int type) {
	Game& game = Game::getInstance();

	SpriteSheetComponent ssc;
	ssc.texture = spritesheet;
	ssc.spriteWidth = 32;
	ssc.spriteHeight = 32;
	ssc.numRows = 5;
	ssc.numCols = 5;

	Animation anim;
	using namespace TileTypes;
	switch (type) {
	case GRASS_TL_WATER:
	case GRASS_TM_WATER:
	case GRASS_TR_WATER:
	case GRASS_ML_WATER:
	case GRASS:
	case GRASS_MR_WATER:
	case GRASS_BL_WATER:
	case GRASS_BM_WATER:
	case GRASS_BR_WATER:
		anim.frames = { type };
		anim.frameTime = 0.0f;
		anim.loop = false;
		break;
	case WATER_1:
	case WATER_2:
		anim.frames = { WATER_1, WATER_2 };
		anim.frameTime = 0.1f;
		anim.loop = true;

		this->addComponent<BoxCollisionComponent>({ {x, y}, {32,32} });

		break;
	default:
		anim.frames = { NONE };
		anim.frameTime = 0.0f;
		anim.loop = false;
	}
	ssc.animations["idle"] = anim;
	ssc.currentAnimation = "idle";
	ssc.currentFrame = 0;
	ssc.elapsedTime = 0.0f;

	this->addComponent<SpriteSheetComponent>(ssc);
	this->addComponent<SpriteComponent>({
		SDL_Rect{0,0,0,0},
		SDL_Rect{0,0,32,32},
		NULL,
		0
	});
	this->addComponent<TransformComponent>({x,y,0,0});

	//this->addComponent<BoxCollisionComponent>({ {x, y}, {32,32} });
}

Tile::~Tile() {}

void Tile::start() {

}

void Tile::update(float deltaTime) {

}