#include "VertexArray.h"

using namespace cote::graphic;

cote::graphic::VertexArray::VertexArray( )
{
	unsigned tmpHandler;
	glGenVertexArrays(1, &tmpHandler);
	m_handler=std::shared_ptr<unsigned>(new unsigned(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
	m_ebo = std::make_unique<ElementBuffer>();
	m_vbo = std::make_unique<VertexBuffer>();
}

void cote::graphic::VertexArray::bind()const noexcept 
{
	glBindVertexArray(*m_handler);
}

void cote::graphic::VertexArray::unbind()const noexcept
{
	glBindVertexArray(NULL);
}


void cote::graphic::VertexArray::copyElements(size_t count, const unsigned * data)
{
	bind();
	m_elemCount = count;
	m_ebo->copyData(count, data);
}

void cote::graphic::VertexArray::setLayout(const VertexAttributeLayout & layout)
{
	bind();
	m_vbo->setVertexAttributeLayout(layout);
}

void cote::graphic::VertexArray::setAttributesValues(size_t count, const float* data)
{
	bind();
	m_vbo->copyData(count, data);
}

void cote::graphic::VertexArray::drawElements()
{
	this->bind();
	glDrawElements(GL_TRIANGLES, m_elemCount, GL_UNSIGNED_INT, NULL);
	this->unbind();
}


