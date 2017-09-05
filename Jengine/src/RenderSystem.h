#pragma once
#include "System.h"
#include "Jengine.h"
#include "ShaderLoader.h"
class RenderSystem : public System
{
	Jengine& jengine = Jengine::getInstance();
	GLuint testShader;
public:
	RenderSystem( std::shared_ptr<EntityManager> entityManager );
	// Inherited via System
	virtual void update(float delta)override;
};