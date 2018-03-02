
#include <vector>
#include <iostream>


#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeCamera.h>
#include <GlobalLogger.h>
#include "ATest.h"
#include "ModelTest.h"
#include "BoxTest.h"
int main()
{

	DEBUG_LOG("test loga");
	
	ModelTest test;
	test.work();

	BoxTest btest;
	btest.work();

	return 0;

}