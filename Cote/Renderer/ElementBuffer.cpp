#include "ElementBuffer.h"
#include "GLerror.h"
#include "GlException.h"
#include <string>
using namespace cote::graphic;

ElementBuffer::ElementBuffer()
{
	unsigned* tmpHandler = new unsigned;
	glGenBuffers(1, tmpHandler);

	handler = std::shared_ptr<unsigned>(std::move(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
}



void cote::graphic::ElementBuffer::bind()const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *handler);
}

void cote::graphic::ElementBuffer::unbind()const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void cote::graphic::ElementBuffer::setData(size_t count, const unsigned * data) 
{
	this->bind();
	GlError error;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), (void*)data, GL_STATIC_DRAW);
	if (error.check())
	{
	
		throw GlException(error.getError());
	}
}


