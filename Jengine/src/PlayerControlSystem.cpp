#include "PlayerControlSystem.h"
#include "PlayerComponent.h"
#include "FPSCamera.h"
#include "Input.h"
#include "TransformComponent.h"
#include <glm\ext.hpp>
#include <iostream>

PlayerControlSystem::PlayerControlSystem(std::shared_ptr<EntityManager> em) : System(em)
{
}

void PlayerControlSystem::update(float delta)
{
	// get player entity, should only be one.
	auto player = entityManager->getEntitiesWithComponent<PlayerComponent>()[0];
	auto playerComp = entityManager->getComponentFromEntity<PlayerComponent>(player);
	auto playerCamera = entityManager->getComponentFromEntity<FPSCamera>(player);
	auto playerTrans = entityManager->getComponentFromEntity<TransformComponent>(player);

	if (Input::keyIsHeld(GLFW_KEY_W)) {
		playerTrans->position += playerTrans->front * 10.0f * delta;
	}
	if (Input::keyIsHeld(GLFW_KEY_S)) {
		playerTrans->position -= playerTrans->front * 10.0f * delta;
	}
	if (Input::keyIsHeld(GLFW_KEY_A)) {
		playerTrans->position -= playerTrans->right * 10.0f * delta;
	}
	if (Input::keyIsHeld(GLFW_KEY_D)) {
		playerTrans->position += playerTrans->right * 10.0f * delta;
	}
	if (Input::keyIsHeld(GLFW_KEY_SPACE)) {
		playerTrans->position += glm::vec3(0.0f, 1.0f, 0.0f) * 10.0f * delta;
	}

	if (Input::keyWasPressed(GLFW_KEY_E)) {
		std::cout << "Player name: " << playerComp->playerName << std::endl;
		std::cout << "Player front: " << glm::to_string(playerTrans->front) << std::endl;
		std::cout << "Camera yaw: " << playerCamera->yaw << std::endl;
	}
}
