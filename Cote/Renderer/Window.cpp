#include "Window.h"




Window::Window(int width, int height, const std::string & title):mWidth(width),mHeight(height),mTitle(title), window(nullptr)
{
	init();
}

bool Window::init()
{
	//TODO: glfw init gdzies indziej
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//TODO: dorobic wykrywaie ekranu, monitora
	window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr), glfwDestroyWindow);
	if (!window) {
		std::cerr << "/nFAILED TO CREATE WINDOW";//debugLog
		
		return false;
	}
	glfwMakeContextCurrent(&(*window));
	return true;
}
