#include "ElementBuffer.h"

using namespace cote::graphic;

ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &m_handler);
}

void cote::graphic::ElementBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handler);
}

void cote::graphic::ElementBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void cote::graphic::ElementBuffer::setData(unsigned count, const unsigned * data)
{
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), (void*)data, GL_STATIC_DRAW);
}


ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_handler);
}
