#include "Input.h"
#include <iostream>

std::map<GLint, std::pair<GLboolean, GLboolean>> Input::keyStates;
std::map<GLint, std::pair<GLboolean, GLboolean>> Input::mouseButtonStates;
GLfloat Input::mouseX;
GLfloat Input::mouseY;
GLfloat Input::scrollX;
GLfloat Input::scrollY;



void Input::updateKey( GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mods )
{
	if (action == GLFW_PRESS)
	{
		keyStates[key].first = true;
		keyStates[key].second = true;
	}

	if (action == GLFW_RELEASE)
	{
		keyStates[key].second = false;
	}
}

void Input::updateMouseButton( GLFWwindow *window, GLint button, GLint action, GLint mods )
{
	if (action == GLFW_PRESS)
	{
		mouseButtonStates[button].first = true;
		mouseButtonStates[button].second = true;
	}

	if (action == GLFW_RELEASE)
	{
		mouseButtonStates[button].second = false;
	}
}

void Input::updateStates()
{
	// Clear single key presses after last frame
	for (auto &k : keyStates)
	{
		k.second.first = false;
	}

	for (auto &b : mouseButtonStates)
	{
		b.second.first = false;
	}
}

bool Input::keyWasPressed( GLint key )
{
	if (keyStates[key].first)
		return true;
	return false;
}

bool Input::keyIsHeld( GLint key )
{
	if (keyStates[key].second)
		return true;
	return false;
}

bool Input::mouseButtonWasPressed( GLint button )
{
	if (mouseButtonStates[button].first)
		return true;
	return false;
}

bool Input::mouseButtonIsHeld( GLint button )
{
	if (mouseButtonStates[button].second)
		return true;
	return false;
}

void Input::mouseInput( GLFWwindow * window, double xpos, double ypos )
{
	mouseX = xpos;
	mouseY = ypos;
}
