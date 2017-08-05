#include "Window.h"




Window::Window(int width, int height, const std::string & title):mWidth(width),mHeight(height),mTitle(title),mWindow(nullptr)
{
	init();
}

Window::~Window()
{
	glfwDestroyWindow(mWindow);

}

bool Window::init()
{
	//TODO: glfw init gdzies indziej
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//TODO: dorobic wykrywaie ekranu, monitora
	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
	if (!mWindow) {
		std::cerr << "/nFAILED TO CREATE WINDOW";//debugLog
		glfwTerminate();
		
		return false;
	}
	glfwMakeContextCurrent(mWindow);
	return true;
}
