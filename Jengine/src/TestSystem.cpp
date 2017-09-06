#include "TestSystem.h"
#include "EntityManager.h"
#include <iostream>
#include "TransformComponent.h"
#include "Input.h"
#include "PlayerComponent.h"
#include "DirectionalLightComponent.h"

TestSystem::TestSystem( std::shared_ptr<EntityManager> entityManager ) : System(entityManager)
{
	
}

void TestSystem::update( float delta )
{
	std::vector<unsigned int> lights = entityManager->getEntitiesWithComponent<DirectionalLightComponent>();
	for (auto entity : lights)
	{
		// Do nothing yet	
	}
}
