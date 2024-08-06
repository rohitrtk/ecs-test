//#include "EntityComponentSystem.h"
//
//ComponentManager::ComponentManager() : mTotalEntities(0) {}
//
//const entity ComponentManager::getTotalEntities() const {
//	return mTotalEntities;
//}
//
//entity ComponentManager::createEntity() {
//	static std::size_t entities = 0;
//	++entities;
//	mTotalEntities = entities;
//	return entities;
//}
//
//void SpriteSystem::update(ComponentManager& manager) {
//	for (int e = 1; e <= manager.getTotalEntities(); e++) {
//		if (manager.sprites.contains(e) && manager.transforms.contains(e)) {
//			manager.sprites[e].dst.x = manager.transforms[e].position.x;
//			manager.sprites[e].dst.y = manager.transforms[e].position.y;
//		}
//	}
//}
//
//void SpriteSystem::render(ComponentManager& manager, SDL_Renderer* renderer) {
//	for (int e = 1; e <= manager.getTotalEntities(); e++) {
//		if (manager.sprites.contains(e)) {
//
//			if (manager.spriteSheets.contains(e)) {
//				auto& sprite = manager.sprites[e];
//				auto& spriteSheet = manager.spriteSheets[e];
//
//				if (!spriteSheet.currentAnimation.empty()) {
//					auto& anim = spriteSheet.animations[spriteSheet.currentAnimation];
//					int frameIndex = anim.frames[spriteSheet.currentFrame];
//					int row = frameIndex  / spriteSheet.numCols;
//					int col = frameIndex % spriteSheet.numCols;
//					
//					SDL_Rect srcRect = { 
//						col * spriteSheet.spriteWidth,
//						row * spriteSheet.spriteHeight,
//						spriteSheet.spriteWidth,
//						spriteSheet.spriteHeight
//					};
//
//					sprite.src = srcRect;
//				}
//
//				SDL_RenderCopy(renderer, spriteSheet.texture, &sprite.src, &sprite.dst);
//			}
//			else {
//				SDL_RenderCopy(
//					renderer,
//					manager.sprites[e].texture,
//					&manager.sprites[e].src,
//					&manager.sprites[e].dst
//				);
//			}
//		}
//	}
//}
//
//void TransformSystem::update(ComponentManager& manager, float deltaTime) {
//	for (int e = 1; e <= manager.getTotalEntities(); e++) {
//		if (manager.transforms.contains(e)) {
//			manager.transforms[e].previousPosition = {
//				manager.transforms[e].position.x,
//				manager.transforms[e].position.y
//			};
//			manager.transforms[e].position.x += manager.transforms[e].velocity.x * deltaTime * manager.transforms[e].movementSpeed;
//			manager.transforms[e].position.y += manager.transforms[e].velocity.y * deltaTime * manager.transforms[e].movementSpeed;
//
//			if (manager.transforms[e].velocity.y < 0) manager.transforms[e].movementDirection = TransformComponent::Direction::Up;
//			else if (manager.transforms[e].velocity.y > 0) manager.transforms[e].movementDirection = TransformComponent::Direction::Down;
//			else if (manager.transforms[e].velocity.x > 0) manager.transforms[e].movementDirection = TransformComponent::Direction::Right;
//			else if (manager.transforms[e].velocity.x < 0) manager.transforms[e].movementDirection = TransformComponent::Direction::Left;
//		}
//	}
//}
//
//void MovementSystem::update(ComponentManager& manager) {
//	const Uint8* keys = SDL_GetKeyboardState(nullptr);
//
//	for (int e = 1; e <= manager.getTotalEntities(); e++) {
//		if (manager.transforms.contains(e) && manager.keys.contains(e)) {
//			if (keys[SDL_SCANCODE_A]) manager.transforms[e].velocity.x = -1.0f;
//			if (keys[SDL_SCANCODE_S]) manager.transforms[e].velocity.y = 1.0f;
//			if (keys[SDL_SCANCODE_W]) manager.transforms[e].velocity.y = -1.0f;
//			if (keys[SDL_SCANCODE_D]) manager.transforms[e].velocity.x = 1.0f;
//
//			if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) manager.transforms[e].velocity.x = 0.0f;
//			if (!keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) manager.transforms[e].velocity.y = 0.0f;
//		}
//	}
//}
//
//void CollisionSystem::update(ComponentManager& manager, float deltaTime) {
//	static unsigned int x = 0;
//	for (int e = 1; e <= manager.getTotalEntities(); e++) {
//		if (
//			manager.collisions.contains(e) && 
//			manager.transforms.contains(e) &&
//			manager.keys.contains(e)
//		) {
//			manager.collisions[e].position = manager.transforms[e].position;
//
//			for (int e2 = 1; e2 <= manager.getTotalEntities(); e2++) {
//				if (
//					e != e2 &&
//					manager.collisions.contains(e2) &&
//					checkCollision(manager.collisions[e], manager.collisions[e2])
//				) {
//					printf("COLLIDE %d\n", x);
//					x++;
//
//					manager.transforms[e].position = manager.transforms[e].previousPosition;
//				}
//			}
//		}
//	}
//}
//
//void CollisionSystem::render(ComponentManager& manager, SDL_Renderer* renderer) {
//	for (int e = 1; e <= manager.getTotalEntities(); e++) {
//		if (manager.collisions.contains(e)) {
//			vec2& position = manager.collisions[e].position;
//			vec2& size = manager.collisions[e].size;
//			SDL_Rect outline = { position.x, position.y, size.x, size.y };
//			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
//			SDL_RenderDrawRect(renderer, &outline);
//			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//		}
//	}
//}
//
//bool CollisionSystem::checkCollision(BoxCollisionComponent& a, BoxCollisionComponent& b) {
//	if (
//		isColliding(a, b, BoxCollisionComponent::Left) ||
//		isColliding(a, b, BoxCollisionComponent::Right) ||
//		isColliding(a, b, BoxCollisionComponent::Up) ||
//		isColliding(a, b, BoxCollisionComponent::Down)
//	) {
//		return true;
//	}
//
//	return false;
//}
//
//bool CollisionSystem::isColliding(const BoxCollisionComponent& a, const BoxCollisionComponent& b, int collisionSide) {
//	switch (collisionSide) {
//	case BoxCollisionComponent::Left:
//		return (a.position.x < b.position.x + b.size.x &&
//			a.position.x + a.size.x > b.position.x &&
//			a.position.y < b.position.y + b.size.y &&
//			a.position.y + a.size.y > b.position.y &&
//			(a.enabledCollisions & BoxCollisionComponent::Left) &&
//			(b.enabledCollisions & BoxCollisionComponent::Right));
//	case BoxCollisionComponent::Right:
//		return (a.position.x + a.size.x > b.position.x &&
//			a.position.x < b.position.x + b.size.x &&
//			a.position.y < b.position.y + b.size.y &&
//			a.position.y + a.size.y > b.position.y &&
//			(a.enabledCollisions & BoxCollisionComponent::Right) &&
//			(b.enabledCollisions & BoxCollisionComponent::Left));
//	case BoxCollisionComponent::Up:
//		return (a.position.y < b.position.y + b.size.y &&
//			a.position.y + a.size.y > b.position.y &&
//			a.position.x < b.position.x + b.size.x &&
//			a.position.x + a.size.x > b.position.x &&
//			(a.enabledCollisions & BoxCollisionComponent::Up) &&
//			(b.enabledCollisions & BoxCollisionComponent::Down));
//	case BoxCollisionComponent::Down:
//		return (a.position.y + a.size.y > b.position.y &&
//			a.position.y < b.position.y + b.size.y &&
//			a.position.x < b.position.x + b.size.x &&
//			a.position.x + a.size.x > b.position.x &&
//			(a.enabledCollisions & BoxCollisionComponent::Down) &&
//			(b.enabledCollisions & BoxCollisionComponent::Up));
//	default:
//		return false;
//	}
//}
//
//void AnimationSystem::update(ComponentManager& manager, float deltaTime) {
//	for (auto& [entity, spriteSheet] : manager.spriteSheets) {
//		if (!spriteSheet.currentAnimation.empty()) {
//
//			//auto& transform = manager.transforms[entity];
//			auto& transform = manager.getComponent<TransformComponent>(entity);
//			bool isMoving = transform.velocity.x != 0 || transform.velocity.y != 0;
//
//			if (isMoving) {
//				spriteSheet.currentAnimation = "walk";
//				auto& anim = spriteSheet.animations[spriteSheet.currentAnimation];
//				spriteSheet.elapsedTime += deltaTime;
//
//				if (spriteSheet.elapsedTime >= anim.frameTime) {
//					spriteSheet.elapsedTime = 0.0f;
//					spriteSheet.currentFrame++;
//
//					if (spriteSheet.currentFrame >= anim.frames.size()) {
//						if (anim.loop) {
//							spriteSheet.currentFrame = 0;
//						}
//						else {
//							spriteSheet.currentFrame = anim.frames.size() - 1;
//						}
//					}
//				}
//			}
//			else {
//				spriteSheet.currentAnimation = "idle";
//				spriteSheet.currentFrame = 0;
//				spriteSheet.elapsedTime = 0.0f;
//			}
//
//		}
//	}
//}
//
//template<>
//std::unordered_map<entity, SpriteComponent>& ComponentManager::getComponentMap<SpriteComponent>() {
//	return sprites;
//}
//
//template <>
//std::unordered_map<entity, TransformComponent>& ComponentManager::getComponentMap<TransformComponent>() {
//	return transforms;
//}
//
//template <>
//std::unordered_map<entity, MovementComponent>& ComponentManager::getComponentMap<MovementComponent>() {
//	return keys;
//}
//
//template <>
//std::unordered_map<entity, BoxCollisionComponent>& ComponentManager::getComponentMap<BoxCollisionComponent>() {
//	return collisions;
//}
//
//template <>
//std::unordered_map<entity, SpriteSheetComponent>& ComponentManager::getComponentMap<SpriteSheetComponent>() {
//	return spriteSheets;
//}