#include "Jengine.h"
#include "Input.h"
#include "GameScene.h"
#include "Scene.h"

std::shared_ptr<Jengine> Jengine::instance = std::shared_ptr<Jengine>( nullptr );

Jengine& Jengine::getInstance()
{
	if (!instance)
	{
		instance = std::shared_ptr<Jengine>( new Jengine() );
	}
	return *instance;
}

void Jengine::init()
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );


	// Make window
	window = glfwCreateWindow( this->screenWidth, this->screenHeight, this->windowTitle.c_str(), nullptr, nullptr );
	glfwMakeContextCurrent( this->window );
	glfwSwapInterval( 1 );
	glewExperimental = GL_TRUE;
	glewInit();

	// Set input options
	glfwSetKeyCallback( this->window, Input::updateKey );
	glfwSetMouseButtonCallback( this->window, Input::updateMouseButton );
	glfwSetCursorPosCallback( this->window, Input::mouseInput );
	//glfwSetScrollCallback( this->window, Input::scrollInput );

	// Set viewport size
	glViewport( 0, 0, this->screenWidth, this->screenHeight );

	// OpenGL options
	glEnable( GL_DEPTH_TEST );

	currentScene = std::shared_ptr<Scene>(new GameScene());

	mainLoop();
}

void Jengine::mainLoop()
{
	static bool sceneInit = false;
	while (!glfwWindowShouldClose( this->window ))
	{
		double time = glfwGetTime();
		float delta = time - this->gametime;
		this->gametime = time;
		this->delta = delta;
		Input::updateStates();
		glfwPollEvents();

		// Update the current scene
		if (!sceneInit)
		{
			currentScene->init();
			sceneInit = true;
		}
		globalInput();
		for (std::shared_ptr<System> sys : currentScene->systems)
		{
			sys->update( delta );
		}

		static double updateTimer = 0.0;
		if (updateTimer >= 0.5)
		{
			int fps = (int)(1000.0 / delta / 1000.0);
			glfwSetWindowTitle( window, (windowTitle + " FPS: " + std::to_string( fps )).c_str() );
			updateTimer = 0.0;
		}
		updateTimer += delta;
	}
	glfwTerminate();
}

void Jengine::globalInput()
{
	if (Input::keyWasPressed( GLFW_KEY_ESCAPE ))
	{
		glfwSetWindowShouldClose( window, true );
	}
}

int main()
{
	Jengine::getInstance().init();
	return 0;
}