#pragma once

//#include "EntityComponentSystem.h"
#include "Game.h"
#include "Helpers.h"

class GameObject {
public:

	GameObject() {
		Game& game = Game::getInstance();
		mId = game.getComponentManager().createEntity();
		game.getGameObjectManager().addGameObject(mId, this);
	}

	virtual ~GameObject() {
		Game& game = Game::getInstance();
		game.getGameObjectManager().removeGameObject(this);
	}

	template <typename T>
	void addComponent(T component) {
		Game& game = Game::getInstance();
		game.getComponentManager().addComponent<T>(mId, component);
	}

	template<typename T>
	void getComponent() {
		Game& game = Game::getInstance();
		return game.getComponentManager().getComponent<T>(mId);
	}

	inline entity getEntity() const {
		return mId;
	}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;

	virtual void onCollide(GameObject& other) {}

protected:
	entity mId;
};