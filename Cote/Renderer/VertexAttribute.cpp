#include "VertexAttribute.h"
#include "GlException.h"
#include <GL\glew.h>
#include <glm.hpp>

using namespace cote::graphic;


cote::graphic::VertexAttribute::VertexAttribute(const GLenum dataType, size_t count) :dataType(dataType), count(count)
{
}


cote::graphic::VertexAttribute2f::VertexAttribute2f(VertexAttributeIndex index, const std::vector<glm::vec2>& data) : VertexAttribute2f(data)
{
	this->index = static_cast<unsigned>(index);
}

cote::graphic::VertexAttribute2f::VertexAttribute2f(unsigned index, const  std::vector<glm::vec2>& data) : VertexAttribute2f(data )
{
	this->index = static_cast<unsigned>(index);
}


cote::graphic::VertexAttribute2f::VertexAttribute2f(const std::vector<glm::vec2>& data):VertexAttributeF(data,2)
{
	convertDataImpl(data);
}

void cote::graphic::VertexAttribute2f::convertDataImpl(const std::vector<glm::vec2>& data)
{
	for (auto& vec : data)
	{
		this->data.push_back(vec.x);
		this->data.push_back(vec.y);
	}
}

cote::graphic::VertexAttribute3f::VertexAttribute3f(VertexAttributeIndex index, const std::vector<glm::vec3>& data) :VertexAttribute3f(data)
{
	this->index = static_cast<unsigned>(index);
}

cote::graphic::VertexAttribute3f::VertexAttribute3f(unsigned index, const std::vector<glm::vec3>& data) : VertexAttribute3f(data)
{
	this->index = index;
}


cote::graphic::VertexAttribute3f::VertexAttribute3f(const std::vector<glm::vec3>& data): VertexAttributeF(data,3)
{
	convertDataImpl(data);
}

void cote::graphic::VertexAttribute3f::convertDataImpl(const std::vector<glm::vec3>& data)
{
	for (auto& vec : data)
	{
		this->data.push_back(vec.x);
		this->data.push_back(vec.y);
		this->data.push_back(vec.z);
	}

}
