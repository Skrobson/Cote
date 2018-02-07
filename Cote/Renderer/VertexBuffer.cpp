#include "VertexBuffer.h"
#include "GlException.h"
#include "GLerror.h"
#include <iostream>
using namespace cote::graphic;

void cote::graphic::VertexBuffer::bind()const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, *handler);
}

void cote::graphic::VertexBuffer::unbind()const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

cote::graphic::VertexBuffer::VertexBuffer(const VertexAttributeLayout & layout)
{
	unsigned* tmpHandler = new unsigned;
	glGenBuffers(1, tmpHandler);
	handler = std::shared_ptr<unsigned>(std::move(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
	setVertexAttributeLayout(layout);
}

void cote::graphic::VertexBuffer::setVertexAttributeLayout(const VertexAttributeLayout& layout)
{
	size_t offset = 0;
	auto attributes = layout.getAttributes();
	this->bind();
	GlError error;
	glBufferData(GL_ARRAY_BUFFER, layout.getSizeOf(), NULL, GL_STATIC_DRAW);
	if (error.check())
	{
		throw GlException(error.getError());
	}

	for (auto &a : attributes)
	{	
		error.clear();
		auto attribute = a.first;
		glEnableVertexAttribArray(attribute->getIndex());
		if (error.check())
		{
			throw GlException(error.getError());
		}
		
	
		glBufferSubData(GL_ARRAY_BUFFER, offset, attribute->getSize(), attribute->getRawData());
		error.clear();
		if (error.check())
		{
			throw GlException(error.getError());
		}
		
		glVertexAttribPointer(attribute->getIndex(), attribute->getCount(), attribute->getType(), GL_FALSE, 0, (GLvoid*)a.second);

		error.clear();
		if (error.check())
		{
			throw GlException(error.getError());
		}

		offset += attribute->getSize();
	}

}


