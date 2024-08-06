#include "ComponentManager.h"
#include "GameObject.h"

ComponentManager::ComponentManager() : mTotalEntities(0) {}

const entity ComponentManager::getTotalEntities() const {
	return mTotalEntities;
}

entity ComponentManager::createEntity() {
	static std::size_t entities = 0;
	++entities;
	mTotalEntities = entities;
	return entities;
}

CameraComponent& getCamera(ComponentManager& manager) {
	for (auto it = manager.cameras.begin(); it != manager.cameras.end(); ++it) {
		return it->second;
	}

	throw std::runtime_error("No camera found!");
}

template<>
std::unordered_map<entity, SpriteComponent>& ComponentManager::getComponentMap<SpriteComponent>() {
	return sprites;
}

template <>
std::unordered_map<entity, TransformComponent>& ComponentManager::getComponentMap<TransformComponent>() {
	return transforms;
}

template <>
std::unordered_map<entity, MovementComponent>& ComponentManager::getComponentMap<MovementComponent>() {
	return keys;
}

template <>
std::unordered_map<entity, BoxCollisionComponent>& ComponentManager::getComponentMap<BoxCollisionComponent>() {
	return collisions;
}

template <>
std::unordered_map<entity, SpriteSheetComponent>& ComponentManager::getComponentMap<SpriteSheetComponent>() {
	return spriteSheets;
}

template <>
std::unordered_map<entity, CameraComponent>& ComponentManager::getComponentMap<CameraComponent>() {
	return cameras;
}