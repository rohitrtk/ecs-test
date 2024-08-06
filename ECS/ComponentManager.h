#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "Helpers.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "BoxCollisionComponent.h"
#include "SpriteSheetComponent.h"
#include "CameraComponent.h"

class GameObject;

class ComponentManager {
public:
	ComponentManager();

	entity createEntity();

	const entity getTotalEntities() const;

	template <typename T>
	void addComponent(entity e, T component) {
		getComponentMap<T>()[e] = component;
	}

	template <typename T>
	T& getComponent(entity e) {
		return getComponentMap<T>()[e];
	}


	std::unordered_map<entity, SpriteComponent> sprites;
	std::unordered_map<entity, TransformComponent> transforms;
	std::unordered_map<entity, MovementComponent> keys;
	std::unordered_map<entity, BoxCollisionComponent> collisions;
	std::unordered_map<entity, SpriteSheetComponent> spriteSheets;
	std::unordered_map<entity, CameraComponent> cameras;

private:
	entity mTotalEntities;

	template <typename T>
	std::unordered_map<entity, T>& getComponentMap();
};

CameraComponent& getCamera(ComponentManager& manager);