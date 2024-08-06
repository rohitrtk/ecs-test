#pragma once

#include <stdio.h>
#include <cstdlib>

#include "Helpers.h"
#include "ComponentManager.h"
#include "SpriteSystem.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "AnimationSystem.h"

#include "GameObjectManager.h"

struct SDL_Window;
struct SDL_Renderer;

constexpr int DEFAULT_WINDOW_WIDTH = 800;
constexpr int DEFAULT_WINDOW_HEIGHT = 600;

class Game {
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}

	Game();
	~Game();

	bool isRunning() const;

	void readInput();
	void update(float deltaTime);
	void render();

	ComponentManager& getComponentManager();
	GameObjectManager& getGameObjectManager();
	SDL_Renderer* getRenderer();

	void setWindowDimensions(std::size_t width, std::size_t height);

private:
	std::size_t mWidth;
	std::size_t mHeight;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	bool mIsRunning;

	ComponentManager mComponentManager;
	SpriteSystem mSpriteSystem;
	TransformSystem mTransformSystem;
	CameraSystem mCameraSystem;
	MovementSystem mMovementSystem;
	CollisionSystem mCollisionSystem;
	AnimationSystem mAnimationSystem;

	GameObjectManager mGameObjectManager;
};
