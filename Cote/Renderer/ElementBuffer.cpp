#include "ElementBuffer.h"

using namespace cote::graphic;

ElementBuffer::ElementBuffer()
{
	unsigned* tmpHandler = new unsigned;
	glGenBuffers(1, tmpHandler);

	m_handler = std::shared_ptr<unsigned>(std::move(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
}



void cote::graphic::ElementBuffer::bind()const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_handler);
}

void cote::graphic::ElementBuffer::unbind()const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void cote::graphic::ElementBuffer::copyData(size_t count, const unsigned * data) noexcept
{
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), (void*)data, GL_STATIC_DRAW);
}


