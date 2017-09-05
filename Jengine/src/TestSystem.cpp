#include "TestSystem.h"
#include "EntityManager.h"
#include <iostream>
#include "TransformComponent.h"
#include "Input.h"
#include "PlayerComponent.h"

TestSystem::TestSystem( std::shared_ptr<EntityManager> entityManager ) : System(entityManager)
{
	
}

void TestSystem::update( float delta )
{
	std::vector<unsigned int> positionEntities = entityManager->getEntitiesWithComponent<TransformComponent>();
	for (auto entity : positionEntities)
	{
		if (!entityManager->hasComponent<PlayerComponent>(entity)) {
			std::shared_ptr<TransformComponent> positionComponent = entityManager->getComponentFromEntity<TransformComponent>(entity);
			positionComponent->rotate(glm::vec3(0.0f, 90.0f * glfwGetTime(), 0.0f));
			if (Input::keyIsHeld(GLFW_KEY_Q)) {
				positionComponent->translate(positionComponent->position + positionComponent->front * delta * 10.0f);
			}
		}
	}
}
