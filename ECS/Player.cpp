#include "Player.h"
//#include "EntityComponentSystem.h"
#include <SDL_image.h>

#include "SpriteSheetComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "BoxCollisionComponent.h"
#include "MovementComponent.h"
#include "CameraComponent.h"

Player::Player() : GameObject() {
	Game& game = Game::getInstance();

	SpriteSheetComponent ssc;
	ssc.texture = IMG_LoadTexture(game.getRenderer(), "res/ss.png");
	ssc.spriteWidth = 32;
	ssc.spriteHeight = 32;
	ssc.numRows = 1;
	ssc.numCols = 3;

	if (!ssc.texture) {
		printf("Error: Failed to load texture from 'res/ss.png'");
	}

	Animation walkAnimation;
	walkAnimation.frames = { 0,1,2 };
	walkAnimation.frameTime = 0.1f;
	walkAnimation.loop = true;

	Animation idleAnimation = walkAnimation;
	idleAnimation.frames = { 0 };
	idleAnimation.loop = false;

	ssc.animations["walk"] = walkAnimation;
	ssc.animations["idle"] = idleAnimation;
	ssc.currentAnimation = "idle";
	ssc.currentFrame = 0;
	ssc.elapsedTime = 0.0f;

	this->addComponent<SpriteSheetComponent>(ssc);
	this->addComponent<SpriteComponent>({
		SDL_Rect{0,0,0,0},
		SDL_Rect{0,0,48,48},
		NULL,
		0
	});
	this->addComponent<TransformComponent>({ 100, 100, 0, 0 });
	this->addComponent<BoxCollisionComponent>({ 10, 10, 48, 48 });
	this->addComponent<MovementComponent>({});
	this->addComponent<CameraComponent>({ vec2{0,0} });
}

Player::~Player() {}

void Player::start() {
	std::printf("Player go beep boop.");
}

void Player::update(float deltaTime) {

}

void Player::onCollide(GameObject& go) {
	std::printf("Player is colliding with something");
}