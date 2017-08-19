#include "VertexBuffer.h"
#include <iostream>
using namespace cote::graphic;

VertexBuffer::VertexBuffer()
{
	unsigned* tmpHandler = new unsigned;
	glGenBuffers(1, tmpHandler);
	m_handler = std::shared_ptr<unsigned>(std::move(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
}



void cote::graphic::VertexBuffer::bind()const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, *m_handler);
}

void cote::graphic::VertexBuffer::unbind()const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cote::graphic::VertexBuffer::setVertexAttributeLayout(const VertexAttributeLayout& layout)
{
	auto attributes = layout.getAttributes();
	for (auto &a : attributes)
	{
		glVertexAttribPointer(a.m_index, a.m_count, a.m_type, a.m_normalized, layout.getStride() , (GLvoid*)a.m_offset);
		glEnableVertexAttribArray(a.m_index);

	}

}


void cote::graphic::VertexBuffer::copyData(size_t size , const float* data)
{
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

