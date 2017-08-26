#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "VertexArray.h"
#include <memory>
#include "Window.h"
#include "Textureold.h"
#include "ShaderProgram.h"
#include <glm.hpp> 
class Test
{
public:
	Test();
	void start();
	~Test();
	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::unique_ptr<cote::graphic::ShaderProgram> program;
	Window* window;
	Texture* tex;
	std::unique_ptr< cote::graphic::VertexArray> vertexArray ;
};

