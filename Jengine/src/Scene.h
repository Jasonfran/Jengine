#pragma once
#include "EntityManager.h"
#include "System.h"

class Scene
{
public:
	std::shared_ptr<EntityManager> entityManager;
	std::vector<std::shared_ptr<System>> systems;
	Scene() {
		entityManager = std::shared_ptr<EntityManager>( new EntityManager() );
	};
	virtual ~Scene() {};
	virtual void init() = 0;
};