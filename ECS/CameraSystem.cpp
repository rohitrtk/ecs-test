#include "CameraSystem.h"

void CameraSystem::update(ComponentManager& manager, float deltaTime) {
	for (auto& [entity, camera] : manager.cameras) {
		if (manager.transforms.contains(entity)) {
			auto& transform = manager.transforms[entity];

			camera.position.x = transform.position.x - (800.0f / 2.0f) + ( 32.0f / 2.0f );
			camera.position.y = transform.position.y - (600.0f / 2.0f) + ( 32.0f / 2.0f );

			/*std::printf("Camera Position: (%f, %f)\n", camera.position.x, camera.position.y);*/
		}
	}
}