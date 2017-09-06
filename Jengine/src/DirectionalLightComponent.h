#pragma once
#include "Component.h"
#include <glm\glm.hpp>

class DirectionalLightComponent : public Component {
public:
	glm::vec3 colour;
	glm::vec3 direction;
	DirectionalLightComponent(glm::vec3 colour, glm::vec3 direction) : colour(colour), direction(direction) {

	}
};