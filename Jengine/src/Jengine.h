#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <memory>

class Renderer {};
class Scene;
class Jengine
{
	static std::shared_ptr<Jengine> instance;
	double gametime = 0.0;
	Jengine() {};
	Jengine( Jengine const& ) {};
	Jengine& operator=( Jengine const& ) {};
	std::shared_ptr<Renderer> renderer;
	GLfloat delta;
	std::string windowTitle = "Jengine";
	std::shared_ptr<Scene> currentScene;
public:
	GLuint screenWidth = 1980;
	GLuint screenHeight = 1080;
	GLFWwindow* window;
	static Jengine& getInstance();
	void init();
	void mainLoop();
	void globalInput();
};