#include "Input.h"
#include  <stdexcept>

std::array<bool, InputHandler::KEY_RANGE>  InputHandler::mKeys = { false };
std::array<bool, InputHandler::KEY_MODIFIER_RANGE> InputHandler::mKeyModifiers = { false };
std::array<bool, InputHandler::MOUSE_BUTTONS_RANGE> InputHandler::mMouseButtons = { false };

double InputHandler::mXpos = 0;
double InputHandler::mYpos = 0;
double InputHandler::mXscroll=0;
double InputHandler::mYscroll=0;

InputHandler::InputHandler(std::shared_ptr< Window> window) : mWindow(window)
{
	glfwSetKeyCallback(*mWindow, key_callback);
	glfwSetCursorPosCallback(*mWindow, cursor_position_callback);
	glfwSetMouseButtonCallback(*mWindow, mouse_button_callback);
	glfwSetScrollCallback(*mWindow, scroll_callback);
}

bool InputHandler::operator()(int key)
{
	bool tmp;
	try {
		tmp= mKeys.at(key);
	}
	catch (std::out_of_range)
	{
		tmp = false;
	}
	return tmp;
}

bool InputHandler::keyEvent(int key)
{
	bool tmp;
	try {
		tmp = mKeys.at(key);
	}
	catch (std::out_of_range)
	{
		tmp = false;
	}
	return tmp;
}

bool InputHandler::mouseButtonEvent(int button)
{
	bool tmp;
	try {
		tmp = mMouseButtons.at(button);
	}
	catch (std::out_of_range)
	{
		tmp = false;
	}
	return tmp;
}

glm::vec2 InputHandler::mousePosition()
{
	return glm::vec2(mXpos,mYpos);
}

glm::vec2 InputHandler::mouseScroll()
{
	return glm::vec2(mXscroll,mYscroll);
}

InputHandler::~InputHandler()
{
}


void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	mKeyModifiers.fill(false);
	if (key >= 0 && key < KEY_RANGE)
	{
		if (action == GLFW_PRESS)		//The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.
			mKeys[key] = true;
		else if (action == GLFW_RELEASE)
			mKeys[key] = false;
	}
	if (mode >= 0 && mode < KEY_MODIFIER_RANGE)
	{
		mKeyModifiers[mode] = true;
	}
}

void InputHandler::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	mXpos = xpos;
	mYpos = ypos;
}

void InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	mKeyModifiers.fill(false);
	if (button >= 0 && button< MOUSE_BUTTONS_RANGE)
	{
		if (action == GLFW_PRESS)		//The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.
			mMouseButtons[button] = true;
		else if (action == GLFW_RELEASE)
			mMouseButtons[button] = false;
	}
	if (mode >= 0 && mode < KEY_MODIFIER_RANGE)
	{
		mKeyModifiers[mode] = true;
	}		
}

void InputHandler::scroll_callback(GLFWwindow* window, double xScroll, double yScroll)
{
	mXscroll = xScroll;
	mYscroll = yScroll;
}