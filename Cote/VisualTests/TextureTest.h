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
#include <Transform.h>

using namespace cote::graphic;

class TextureTest
{
public:
	TextureTest();
	~TextureTest();

	void render();
private:
	std::shared_ptr< cote::graphic::VertexArray> createBox();

	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::shared_ptr<cote::graphic::ShaderProgram> program;
	std::shared_ptr< cote::graphic::VertexArray> vertexArray;
	std::shared_ptr< cote::graphic::VertexArray> box;

	cote::graphic::UniformT<unsigned> texUniform;

	std::shared_ptr<cote::graphic::Texture2d> tex;

	std::shared_ptr<Material> material;

	Renderer renderer;

	std::shared_ptr<UniformT<glm::mat4>> model;
	
	cote::Transform transform;

	glm::mat4 view;
	glm::mat4 projection;
};

