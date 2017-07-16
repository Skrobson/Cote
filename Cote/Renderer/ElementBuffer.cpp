#include "ElementBuffer.h"

using namespace cote::graphic;

ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &m_handler);
}


cote::graphic::ElementBuffer::ElementBuffer(ElementBuffer && other)
{
	this->m_handler = other.m_handler;
	other.m_handler = NULL;
}

void cote::graphic::ElementBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handler);
}

void cote::graphic::ElementBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void cote::graphic::ElementBuffer::copyData(size_t count, const unsigned * data)
{
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), (void*)data, GL_STATIC_DRAW);
}


ElementBuffer::~ElementBuffer()
{
	if(m_handler)
	glDeleteBuffers(1, &m_handler);
}
