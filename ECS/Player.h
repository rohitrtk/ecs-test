#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	virtual ~Player();

	void start() override;
	void update(float deltaTime) override;

	void onCollide(GameObject& other) override;
};

