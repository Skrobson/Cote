#include "VertexAttributeLayout.h"
#include <GL\glew.h>
#include <glm.hpp>
using namespace cote::graphic;

//void cote::graphic::VertexAttributeLayout::pushVertexAttribute(VertexAttributeIndex index,  unsigned count, unsigned size)
//{
//	
//	m_stride += size;
//}

//cote::graphic::VertexAttribute::VertexAttribute(VertexAttributeIndex index, size_t count, size_t offset, size_t size) :m_index(static_cast<unsigned>(index)),
//m_count(count), m_offset(offset), m_size(size)
//{
//}
//
//cote::graphic::VertexAttribute::VertexAttribute(unsigned index, size_t count, size_t offset, size_t size) : m_index(index),
//m_count(count), m_offset(offset), m_size(size)
//{
//}

cote::graphic::VertexAttribute2f::VertexAttribute2f(VertexAttributeIndex index,const std::vector<glm::vec2>& data)
{
	m_index = static_cast<unsigned>(index);
	m_count = 2;
	m_size = sizeof(float) * m_count * data.size();
	m_SpecData = data;
	convertData();
}

cote::graphic::VertexAttribute2f::VertexAttribute2f(unsigned index,const  std::vector<glm::vec2>& data)
{
	m_index = static_cast<unsigned>(index);
	m_count = 2;
	m_size = sizeof(float) * m_count * data.size();

	m_SpecData = data;
	convertData();
}

void cote::graphic::VertexAttribute2f::convertData()
{
	for (auto& vec : m_SpecData)
	{
		m_data.push_back(vec.x);
		m_data.push_back(vec.y);
	}
	m_SpecData.clear();
}

cote::graphic::VertexAttribute3f::VertexAttribute3f(VertexAttributeIndex index,  const std::vector<glm::vec3>& data)
{
	m_index = static_cast<unsigned>(index);
	m_count = 3;
	m_size = sizeof(float) * m_count * data.size();

	m_SpecData = data;
	convertData();
}

cote::graphic::VertexAttribute3f::VertexAttribute3f(unsigned index, const std::vector<glm::vec3>& data)
{
	m_index = index;
	m_count = 3;
	m_size = sizeof(float) * m_count * data.size();

	m_SpecData = data;
	convertData();
}

void cote::graphic::VertexAttribute3f::convertData()
{
	for (auto& vec : m_SpecData)
	{
		m_data.push_back(vec.x);
		m_data.push_back(vec.y);
		m_data.push_back(vec.z);
	}
	m_SpecData.clear();
}

void cote::graphic::VertexAttributeLayout::pushVertexAttribute(std::shared_ptr<VertexAttribute> attribute)
{
	
	auto tmpAttribute = std::make_pair(attribute, m_size);
	m_attributes.push_back(tmpAttribute);
	m_size += attribute->getSize();
}
