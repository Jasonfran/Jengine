#include "FPSCameraSystem.h"
#include <GL\glew.h>
#include "EntityManager.h"
#include <iostream>
#include "Input.h"
#include "TransformComponent.h"

FPSCameraSystem::FPSCameraSystem(std::shared_ptr<EntityManager> em) : System(em)
{
}

void FPSCameraSystem::update(float delta)
{
	std::vector<GLuint> entities = entityManager->getEntitiesWithComponent<FPSCamera>();
	if (entities.size() > 1) {
		std::cout << "More than one FPSCamera component in game. Will only use first one seen." << std::endl;
	}
	else if (entities.size() == 1) {
		std::shared_ptr<FPSCamera> camera = entityManager->getComponentFromEntity<FPSCamera>(entities[0]);
		std::shared_ptr<TransformComponent> transform = entityManager->getComponentFromEntity<TransformComponent>(entities[0]);
		if (!camera->initialised) {
			setupCamera(camera);
			transform->front = glm::vec3(0.0f, 0.0f, -1.0f);
		}
		
		glm::vec2 mousePos = Input::getMousePos();
		
		if (camera->firstMouse) {
			lastX = mousePos.x;
			lastY = mousePos.y;
			camera->firstMouse = false;
		}

		float xoffset = mousePos.x - lastX;
		float yoffset = lastY - mousePos.y;
		lastX = mousePos.x;
		lastY = mousePos.y;

		xoffset *= camera->mouseSensitivity;
		yoffset *= camera->mouseSensitivity;

		camera->yaw += xoffset;
		camera->pitch += yoffset;
		
		if (camera->pitch > 89.0f)
			camera->pitch = 89.0f;
		if (camera->pitch < -89.0f)
			camera->pitch = -89.0f;

		if (camera->yaw > 360.0f)
			camera->yaw = fmod(camera->yaw, 360.0f);
		if (camera->yaw < 0.0f)
			camera->yaw += 360.0f;

		transform->rotate(glm::vec3(-camera->pitch, -camera->yaw, 0.0f));

		//transform->right = glm::normalize(glm::cross(transform->front, worldUp));
		//transform->up = glm::normalize(glm::cross(transform->right, transform->front));
	}
}

void FPSCameraSystem::setupCamera(std::shared_ptr<FPSCamera> camera)
{
	camera->yaw = -90.0f;
	camera->pitch = 0.0f;
	camera->initialised = true;
	glfwSetInputMode(Jengine::getInstance().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
