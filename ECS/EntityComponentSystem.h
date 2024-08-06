//#pragma once
//
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <cstdio>
//#include <unordered_map>
//#include <string>
//#include <vector>
//
//using entity = std::size_t;
//
//struct vec2 {
//	float x;
//	float y;
//};
//
//#pragma region Components
//
//struct SpriteComponent {
//	SDL_Rect src;
//	SDL_Rect dst;
//	SDL_Texture* texture;
//
//	int spriteIndex = -1;
//};
//
//struct Animation {
//	std::vector<int> frames;
//	float frameTime;
//	bool loop;
//};
//
//struct SpriteSheetComponent {
//	SDL_Texture* texture;
//
//	int spriteWidth;
//	int spriteHeight;
//	int numRows;
//	int numCols;
//
//	std::unordered_map<std::string, Animation> animations;
//	std::string currentAnimation;
//	int currentFrame;
//	float elapsedTime;
//};
//
//struct TransformComponent {
//	vec2 position = { 0, 0 };
//	vec2 velocity = { 0, 0 };
//
//	vec2 previousPosition = { 0,0 };
//
//	float movementSpeed = 500.f;
//
//	enum Direction {
//		None,
//		Right,
//		Left,
//		Up,
//		Down
//	};
//
//	Direction movementDirection = None;
//};
//
//struct MovementComponent {};
//
//struct BoxCollisionComponent {
//	vec2 position = { 0, 0 };
//	vec2 size = { 0,0 };
//
//	enum Collisions {
//		None	= 0,
//		Left	= 1 << 0,
//		Right	= 1 << 1,
//		Up		= 1 << 2,
//		Down	= 1 << 3
//	};
//
//	int enabledCollisions =
//		Collisions::Left	|
//		Collisions::Right	|
//		Collisions::Up		|
//		Collisions::Down;
//};
//
//struct ComponentManager {
//public:
//	ComponentManager();
//
//	entity createEntity();
//
//	const entity getTotalEntities() const;
//
//	template <typename T>
//	void addComponent(entity e, T component) {
//		getComponentMap<T>()[e] = component;
//	}
//
//	template <typename T>
//	T& getComponent(entity e) {
//		return getComponentMap<T>()[e];
//	}
//	
//	std::unordered_map<entity, SpriteComponent> sprites;
//	std::unordered_map<entity, TransformComponent> transforms;
//	std::unordered_map<entity, MovementComponent> keys;
//	std::unordered_map<entity, BoxCollisionComponent> collisions;
//	std::unordered_map<entity, SpriteSheetComponent> spriteSheets;
//
//private:
//	entity mTotalEntities;
//
//	template <typename T>
//	std::unordered_map<entity, T>& getComponentMap();
//};
//
//#pragma endregion Components
//
//#pragma region Systems
//
//struct SpriteSystem {
//	void update(ComponentManager& manager);
//	void render(ComponentManager& manager, SDL_Renderer* renderer);
//};
//
//struct TransformSystem {
//	void update(ComponentManager& manager, float deltaTime);
//};
//
//struct MovementSystem {
//	void update(ComponentManager& manager);
//};
//
//struct CollisionSystem {
//	void update(ComponentManager& manager, float deltaTime);
//	void render(ComponentManager& manager, SDL_Renderer* renderer);
//
//	bool checkCollision(BoxCollisionComponent& a, BoxCollisionComponent& b);
//	bool isColliding(const BoxCollisionComponent& a, const BoxCollisionComponent& b, int collisionSide);
//};
//
//struct AnimationSystem {
//	void update(ComponentManager& manager, float deltaTime);
//};
//
//#pragma endregion