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

void GameScene::init()
{
	systems.push_back(std::shared_ptr<TestSystem>(new TestSystem(entityManager)));
	systems.push_back(std::shared_ptr<RenderSystem>(new RenderSystem(entityManager)));
	systems.push_back(std::shared_ptr<FPSCameraSystem>(new FPSCameraSystem(entityManager)));
	systems.push_back(std::shared_ptr<PlayerControlSystem>(new PlayerControlSystem(entityManager)));

	GLuint entity1 = entityManager->create();
	entityManager->addComponent(entity1, std::shared_ptr<PlayerComponent>(new PlayerComponent()));
	entityManager->addComponent(entity1, std::shared_ptr<FPSCamera>(new FPSCamera(45.0f, 0.1f)));
	entityManager->addComponent(entity1, std::shared_ptr<TransformComponent>(new TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f))));

	GLuint entity2 = entityManager->create();
	entityManager->addComponent(entity2, std::shared_ptr<TransformComponent>(new TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f))));
	entityManager->addComponent(entity2, std::shared_ptr<RenderComponent>(new RenderComponent(glm::vec3(1.0f, 1.0f, 0.0f), ModelLoader::loadModel("models/arrow.obj"))));

}
