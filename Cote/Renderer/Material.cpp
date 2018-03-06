#include "Material.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace cote::graphic;

cote::graphic::Material::Material(std::shared_ptr<ShaderProgram> shader): shader(shader)
{
}

void cote::graphic::Material::addUniform(std::shared_ptr<Uniform> uniform)
{
	uniform->searchForUniformLocation(shader);
	uniforms.push_back(uniform);
}

void cote::graphic::Material::addTexture(std::shared_ptr<Texture> texture)
{
	UniformT<int> texSampler(texture->getSamplerName());
	texSampler.searchForUniformLocation(shader);
	textures.push_back(std::make_pair(texture,texSampler));
}

void cote::graphic::Material::updateUniforms(std::shared_ptr<ShaderProgram> shader)
{
	for (auto uniform : uniforms)
	{
		uniform->updateValueForProgram(shader);
	}
}

void cote::graphic::Material::bindTextures(std::shared_ptr<ShaderProgram> shader)
{
	for (size_t i = 0; i < textures.size(); ++i)
	{
		textures[i].first->bind(i);
		textures[i].second.setValue(i);
		textures[i].second.updateValueForProgram(shader);
	}
}

void cote::graphic::Material::unbindTextures()
{
	for (size_t i = 0; i < textures.size(); ++i)
	{
		textures[i].first->unbind(i);
	}
}

std::shared_ptr<ShaderProgram> cote::graphic::Material::getProgram()
{
	return shader;
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
