#include "VertexBuffer.h"

using namespace cote::graphic;

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_handler);
}


void cote::graphic::VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handler);
}

void cote::graphic::VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cote::graphic::VertexBuffer::setVertexAttributeLayout(const VertexAttributeLayout& layout)
{
	auto attributes = layout.getAttributes();
	for (auto &a : attributes)
	{
		glVertexAttribPointer(a.m_index, a.m_size, a.m_type, a.m_normalized, layout.getStride() , (GLvoid*)a.m_offset);
		glEnableVertexAttribArray(a.m_index);
	}

}


void cote::graphic::VertexBuffer::setData(size_t size , const uint8_t* data)
{
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
	if(m_handler)
	glDeleteBuffers(1, &m_handler);
}