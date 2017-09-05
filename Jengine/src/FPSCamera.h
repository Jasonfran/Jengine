#pragma once
#include "Component.h"
#include <GL\glew.h>
#include <glm\common.hpp>

class FPSCamera : public Component {
public:
	GLboolean initialised = false;
	GLboolean firstMouse = true;
	GLfloat yaw, pitch;

	GLfloat mouseSensitivity;
	GLfloat FOV;

	FPSCamera(GLfloat FOV, GLfloat sensitivity): FOV(FOV), mouseSensitivity(sensitivity) {

	}
};