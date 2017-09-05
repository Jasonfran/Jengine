#pragma once
#include "System.h"
#include "FPSCamera.h"
class FPSCameraSystem : public System {
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat lastX, lastY;
public:
	FPSCameraSystem(std::shared_ptr<EntityManager> em);
	// Inherited via System
	virtual void update(float delta) override;
	void setupCamera(std::shared_ptr<FPSCamera> camera);
};
