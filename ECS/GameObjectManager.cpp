#include "GameObjectManager.h"

#include "GameObject.h"

void GameObjectManager::addGameObject(entity e, GameObject* go) {
	//mGameObjects.push_back(go);
	mGameObjects[e] = go;
}

void GameObjectManager::removeGameObject(GameObject* go) {
	mGameObjects.erase(std::remove(mGameObjects.begin(), mGameObjects.end(), go), mGameObjects.end());
}

void GameObjectManager::start() {
	/*for (GameObject* go : mGameObjects) {
		go->start();
	}*/
	for (auto& [entity, go] : mGameObjects) {
		go->start();
	}
}

void GameObjectManager::update(float deltaTime) {
	/*for (GameObject* go : mGameObjects) {
		go->update(deltaTime);
	}*/
	for (auto& [entity, go] : mGameObjects) {
		go->update(deltaTime);
	}
}

//const std::vector<GameObject*>& GameObjectManager::getGameObjects() const {
//	return mGameObjects;
//}

const std::unordered_map<entity, GameObject*>& GameObjectManager::getGameObjects() {
	return mGameObjects;
}