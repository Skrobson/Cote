
#include <vector>
#include <iostream>


#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeCamera.h>
//#include <GlobalLogger.h>
#include "ATest.h"
#include "ModelTest.h"
#include "BoxTest.h"
#include "MapTest.h"
int main()
{

	//DEBUG_LOG("test loga");
	

	//ModelTest test;
	//test.work();

	//BoxTest btest;
	//btest.work();

	MapTest mTest;
	mTest.work();
	return 0;

}