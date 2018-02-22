#pragma once
#include <vector>
#include <iostream>
#include <memory>

#include "Window.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include "Texture.h"
#include "Bitmap.h"

#include <Uniform.h>
#include <Material.h>
#include <Renderer.h>

using namespace cote::graphic;

class TextureTest
{
public:
	TextureTest();
	~TextureTest();

	void render();
private:

	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::shared_ptr<cote::graphic::ShaderProgram> program;
	std::shared_ptr< cote::graphic::VertexArray> vertexArray;

	cote::graphic::UniformT<unsigned> texUniform;

	std::shared_ptr<cote::graphic::Texture2d> tex;

	std::shared_ptr<Material> material;

	Renderer renderer;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};

