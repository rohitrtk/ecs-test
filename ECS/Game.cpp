#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Game::Game() :
	mWidth(DEFAULT_WINDOW_WIDTH), 
	mHeight(DEFAULT_WINDOW_HEIGHT), 
	mWindow(nullptr), 
	mRenderer(nullptr), 
	mIsRunning(true) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize! SDL Error: %s\n", SDL_GetError());
		mIsRunning = false;
	}

	mWindow = SDL_CreateWindow(
		"Entity Component System Test", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		mWidth, 
		mHeight, 
		SDL_WINDOW_SHOWN
	);

	if (!mWindow) {
		printf("Window failed to initialize! SDL Error: %s\n", SDL_GetError());
		mIsRunning = false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!mRenderer) {
		printf("Renderer failed to initialize! SDL Error: %s\n", SDL_GetError());
		mIsRunning = false;
	}

	//SDL_RenderSetScale(mRenderer, 1.0f, 1.0f);
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image failed to initialize! SDL_image Error: %s\n", IMG_GetError());
		mIsRunning = false;
	}

	if (TTF_Init() < 0) {
		printf("SDL_ttf failed to initialize! SDL_ttf Error: %s\n", TTF_GetError());
		mIsRunning = false;
	}
}

Game::~Game() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::setWindowDimensions(std::size_t width, std::size_t height) {
	SDL_SetWindowSize(mWindow, width, height);
}

bool Game::isRunning() const {
	return mIsRunning;
}

void Game::readInput() {
	SDL_Event e;
	SDL_PollEvent(&e);
	
	const Uint8* keystates = SDL_GetKeyboardState(nullptr);

	if (e.type == SDL_QUIT) {
		mIsRunning = false;
	}

	if (keystates[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

void Game::update(float deltaTime) {
	mMovementSystem.update(mComponentManager);
	mTransformSystem.update(mComponentManager, deltaTime);
	mCollisionSystem.update(mComponentManager, deltaTime);
	mCameraSystem.update(mComponentManager, deltaTime);
	mAnimationSystem.update(mComponentManager, deltaTime);
	mSpriteSystem.update(mComponentManager);
}

void Game::render() {
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	/** Render Here */

	mSpriteSystem.render(mComponentManager, mRenderer);
	mCollisionSystem.render(mComponentManager, mRenderer);

	SDL_RenderPresent(mRenderer);
}

ComponentManager& Game::getComponentManager() {
	return mComponentManager;
}

GameObjectManager& Game::getGameObjectManager() {
	return mGameObjectManager;
}

SDL_Renderer* Game::getRenderer() {
	return mRenderer;
}