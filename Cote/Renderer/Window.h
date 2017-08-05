#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
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
	inline GLFWwindow* getWindow() {
		return mWindow;
	}
	inline operator GLFWwindow*() {
		return mWindow;
	}
	~Window();
private:
	bool init();
	GLFWwindow* mWindow;
	int mWidth, mHeight;
	std::string mTitle;
};

