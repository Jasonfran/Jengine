#pragma once
#include <memory>

class EntityManager;
class System
{
public:
	std::shared_ptr<EntityManager> entityManager;
	System( std::shared_ptr<EntityManager> entityManager )
	{
		this->entityManager = entityManager;
	}
	virtual ~System() {};
	virtual void update(float delta) = 0;
};