
#include <vector>
#include <iostream>


#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeCamera.h>
#include "ATest.h"
#include "ModelTest.h"
#include "BoxTest.h"
int main()
{

	
	
	ModelTest test;
	test.work();

	BoxTest btest;
	btest.work();

	return 0;
}