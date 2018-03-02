#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <memory>
class Window
{
public:
	Window(int mWidth, int height, const std::string& title);

	inline const int& getFrameX() const {
		return mWidth;
	}

	inline const int& getFrameY() const {
		return mHeight;
	}

	inline const GLFWwindow* getWindow()const {
		return &(*window);
	}
	inline operator GLFWwindow*() {
		return &(*window);
	}

private: 
	bool init();
	std::shared_ptr<GLFWwindow> window;
	int mWidth, mHeight; 
	std::string mTitle;
};

