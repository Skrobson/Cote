#pragma once

#include <memory>

#include "Window.h"
#include "Textureold.h"
#include "ShaderProgram.h"
 #include "VertexArray.h"
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

