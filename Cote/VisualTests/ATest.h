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
#include <Model.h>
#include <FreeCamera.h>
#include <AssetManager.h>

using namespace cote::graphic;


class ATest
{
public:
	ATest();
	virtual ~ATest();

	virtual void render();
	virtual void update() = 0;

	virtual void work();
protected:
	Renderer renderer;
	std::shared_ptr< Window> window;

	std::shared_ptr< FreeCamera>  camera;
	cote::AssetManager manager;

	std::vector<std::shared_ptr<Model>> models;



};

