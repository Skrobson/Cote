#include "VertexArray.h"

using namespace cote::graphic;

cote::graphic::VertexArray::VertexArray( )
{
	glGenVertexArrays(1, &m_handler);
	m_ebo = std::make_unique<ElementBuffer>(new ElementBuffer);
	m_vbo = std::make_unique<VertexBuffer>(new VertexBuffer);
}

cote::graphic::VertexArray::VertexArray()
{
}


void cote::graphic::VertexArray::bind()
{
	glBindVertexArray(m_handler);
}

void cote::graphic::VertexArray::unbind()
{
	glBindVertexArray(NULL);
}


void cote::graphic::VertexArray::setElements(size_t count, const unsigned * data)
{
	m_elemCount = count;
	m_ebo->setData(count, data);
}

void cote::graphic::VertexArray::setLayout(const VertexAttributeLayout & layout)
{
	m_vbo->setVertexAttributeLayout(layout);
}

void cote::graphic::VertexArray::setAttributesValues(size_t count, const uint8_t * data)
{
	m_vbo->setData(count, data);
}

VertexArray::~VertexArray()
{
	if(m_handler)
	glDeleteBuffers(1, &m_handler);
}
