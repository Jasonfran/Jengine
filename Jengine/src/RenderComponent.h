#pragma once
#include "Component.h"
#include <glm\glm.hpp>
#include "Model.h"

class RenderComponent : public Component
{
public:
	glm::vec3 colour;
	std::shared_ptr<Model> model;
	RenderComponent( glm::vec3 colour, std::shared_ptr<Model> model) : colour( colour ), model(model) {}
};