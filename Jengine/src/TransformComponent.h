#pragma once
#include "Component.h"
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <iostream>

class TransformComponent : public Component
{
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 eularRotation;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 localToWorld;
	TransformComponent(glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)) : position(position), scale(scale) {

	}

	void translate(glm::vec3 translation) {
		position = translation;
	}

	void translate(GLfloat x, GLfloat y, GLfloat z) {
		position = glm::vec3(x, y, z);
	}

	void rotate(glm::vec3 rotation) {
		this->rotation = glm::quat(glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
		front = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		up = glm::normalize(glm::cross(right, front));
	}



	// Need to get this working so front, up and right vectors are calculated and stuff. Add helper functions
};