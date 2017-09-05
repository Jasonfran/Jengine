#pragma once
#include "System.h"
#include "EntityManager.h"

class PlayerControlSystem : public System {
public:
	PlayerControlSystem(std::shared_ptr<EntityManager> em);

	// Inherited via System
	virtual void update(float delta) override;
};
