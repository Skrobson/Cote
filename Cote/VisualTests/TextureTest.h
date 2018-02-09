#pragma once
#include <vector>
#include <iostream>
#include <memory>

#include "Window.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "Texture.h"
#include "Bitmap.h"
#include <Textureold.h>

class TextureTest
{
public:
	TextureTest();
	~TextureTest();

	void bind();
private:

	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::unique_ptr<cote::graphic::ShaderProgram> program;
	std::unique_ptr< cote::graphic::VertexArray> vertexArray;

	std::unique_ptr<cote::graphic::Texture2d> tex;
	std::unique_ptr<Texture> oldTex;
};

