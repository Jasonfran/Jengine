#include "RenderSystem.h"
#include "ShaderLoader.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EntityManager.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Model.h"
#include "Mesh.h"
#include "FPSCamera.h"
#include "ModelLoader.h"
#include <iostream>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm/ext.hpp>

RenderSystem::RenderSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager)
{
	testShader = ShaderLoader::loadShader( "shaders/test.vert", "shaders/test.frag" );
}

void RenderSystem::update( float delta )
{
	glEnable( GL_DEPTH_TEST );
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glm::mat4 projection = glm::perspective( glm::radians( 45.0f ), (float)jengine.screenWidth / (float)jengine.screenHeight, 0.1f, 100.0f );
	glm::mat4 view;
	auto cameraEntities = entityManager->getEntitiesWithComponent<FPSCamera>();
	if (cameraEntities.size() > 0) {
		auto camera = entityManager->getComponentFromEntity<FPSCamera>(cameraEntities[0]);
		auto cameraTrans = entityManager->getComponentFromEntity<TransformComponent>(cameraEntities[0]);
		view = glm::lookAt(cameraTrans->position, cameraTrans->position + cameraTrans->front, cameraTrans->up);
		/*view = glm::rotate(view, -camera->pitch * 0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, camera->yaw * 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, cameraTrans->position);*/
	}
	else {
		std::cout << "No FPSCamera found..." << std::endl;
	}

	for (GLuint entityID : entityManager->getEntitiesWithComponent<RenderComponent>())
	{
		std::shared_ptr<TransformComponent> positionData = entityManager->getComponentFromEntity<TransformComponent>( entityID );
		std::shared_ptr<RenderComponent> renderData = entityManager->getComponentFromEntity<RenderComponent>( entityID );
		glUseProgram( testShader );
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
		translationMatrix = glm::translate( translationMatrix, positionData->position);
		rotationMatrix = glm::toMat4(positionData->rotation);
		scaleMatrix = glm::scale(scaleMatrix, positionData->scale);

		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		ShaderLoader::setMatrix4( testShader, "MVP", projection * view * modelMatrix );
		ShaderLoader::setMatrix4(testShader, "model", modelMatrix);
		ShaderLoader::setVector3f( testShader, "colour", renderData->colour );
		for (auto mesh : renderData->model->meshes) {
			glBindVertexArray( mesh->VAO );
			glDrawElements( GL_TRIANGLES, mesh->vertices.size(), GL_UNSIGNED_INT, 0 );
			glBindVertexArray( 0 );
		}

		
	}
	glfwSwapBuffers( jengine.window );
}
