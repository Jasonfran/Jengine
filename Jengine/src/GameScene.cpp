#include "GameScene.h"
#include <iostream>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TestSystem.h"
#include "RenderSystem.h"
#include "Model.h"
#include "ModelLoader.h"
#include "FPSCamera.h"
#include "FPSCameraSystem.h"
#include "PlayerControlSystem.h"
#include "PlayerComponent.h"
#include "DirectionalLightComponent.h"

void GameScene::init()
{
	systems.push_back(std::shared_ptr<TestSystem>(new TestSystem(entityManager)));
	systems.push_back(std::shared_ptr<PlayerControlSystem>(new PlayerControlSystem(entityManager)));
	systems.push_back(std::shared_ptr<FPSCameraSystem>(new FPSCameraSystem(entityManager)));
	systems.push_back(std::shared_ptr<RenderSystem>(new RenderSystem(entityManager)));

	GLuint playerEntity = entityManager->create();
	entityManager->addComponent(playerEntity, std::shared_ptr<PlayerComponent>(new PlayerComponent()));
	entityManager->addComponent(playerEntity, std::shared_ptr<FPSCamera>(new FPSCamera(45.0f, 0.1f)));
	entityManager->addComponent(playerEntity, std::shared_ptr<TransformComponent>(new TransformComponent(glm::vec3(0.0f, 5.0f, 0.0f))));

	GLuint testLight = entityManager->create();
	entityManager->addComponent(testLight, std::shared_ptr<DirectionalLightComponent>(new DirectionalLightComponent(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));

	GLuint testLight2 = entityManager->create();
	entityManager->addComponent(testLight2, std::shared_ptr<DirectionalLightComponent>(new DirectionalLightComponent(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f))));

	int width = 5;
	int height = 5;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			GLuint entity = entityManager->create();
			entityManager->addComponent(entity, std::shared_ptr<TransformComponent>(new TransformComponent(glm::vec3(0.0f + 10.0f * i, 0.0f, 0.0f + 10.0f * j), glm::vec3(10.0f, 10.0f, 10.0f))));
			entityManager->addComponent(entity, std::shared_ptr<RenderComponent>(new RenderComponent(glm::vec3((1.0/width) * i, (1.0/height) * j, 1.0f), ModelLoader::loadModel("models/cube.obj"))));
		}
	}

}
