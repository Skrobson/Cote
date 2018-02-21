#include "Material.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

cote::graphic::Material::Material(std::shared_ptr<ShaderProgram> shader): shader(shader)
{
}

void cote::graphic::Material::addUniform(std::shared_ptr<Uniform> uniform)
{
	uniform->searchForUniformLocation(shader);
}

void cote::graphic::Material::addTexture(std::shared_ptr<Texture> texture)
{
	UniformT<int> texSampler(texture->getSamplerName());
	texSampler.searchForUniformLocation(shader);
	textures.push_back(std::make_pair(texture,texSampler));
}


void cote::graphic::Material::render()
{
	shader->bind();

	for (auto uniform : uniforms) 
	{
		uniform->updateValueForProgram(shader);
	}

	for (size_t i = 0; i < textures.size(); ++i)
	{
		textures[i].first->bind(i);
		textures[i].second.setValue(i);
		textures[i].second.updateValueForProgram(shader);
	}

	vao->bind();
	vao->drawElements();
	vao->unbind();

	for (size_t i = 0; i < textures.size(); ++i)
	{
		textures[i].first->bind(i);
		textures[i].second.setValue(i);
		textures[i].second.updateValueForProgram(shader);
	}
}

cote::graphic::Material::~Material()
{
}

void cote::graphic::Material::setTexturesUniforms()
{
	for (auto tex : textures)
	{
		tex.second.searchForUniformLocation(shader);
	}
}
