#pragma once

#include <unordered_map>
#include "Helpers.h"

class GameObject;

class GameObjectManager {
public:
	void addGameObject(entity e, GameObject* go);
	void removeGameObject(GameObject* go);
	
	void start();
	void update(float deltaTime);

	//const std::vector<GameObject*>& getGameObjects() const;
	const std::unordered_map<entity, GameObject*>& getGameObjects();

private:
	//std::vector<GameObject*> mGameObjects;
	std::unordered_map<entity, GameObject*> mGameObjects;
};