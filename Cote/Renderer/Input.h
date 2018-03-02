#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <array>

#include "Window.h"
#include <memory>

namespace cote
{
	//narazie odpowiedzialny za mysz i klawiature
	//z powodu glfwCallback funkcje i tablice musza byc statyczne
	//glfwGetMouseButton() i inne, glwf ma juz wlasna zdefiniowana tablice
	//TODO: rozdzielic na wiecej klas, zdefiniowac enumy
	class InputHandler
	{
	public:
		InputHandler(std::shared_ptr< Window> window);
		bool operator()(int key);
		bool keyEvent(int key);
		bool mouseButtonEvent(int button);
		glm::vec2 mousePosition();
		glm::vec2 mouseScroll();
		~InputHandler();
	private:
		std::shared_ptr< Window> mWindow;
		//keyboard
		static const uint16_t KEY_RANGE = 349;//form glfw documentation
		static const uint8_t KEY_MODIFIER_RANGE = 9;
		static std::array<bool, KEY_RANGE>  mKeys;
		static std::array<bool, KEY_MODIFIER_RANGE> mKeyModifiers;
		//mouse
		static const uint8_t MOUSE_BUTTONS_RANGE = 8;
		static std::array<bool, MOUSE_BUTTONS_RANGE> mMouseButtons;
		static double mXpos;
		static double mYpos;
	
		static double mXscroll;
		static double mYscroll;
	
		//callbacks
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow * window, double xScroll, double yScroll);
	};
}


