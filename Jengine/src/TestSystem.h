#pragma once
#include "System.h"

class TestSystem : public System
{
public:
	unsigned int entity1;
	TestSystem( std::shared_ptr<EntityManager> entityManager);
	virtual void update(float delta) override;
};