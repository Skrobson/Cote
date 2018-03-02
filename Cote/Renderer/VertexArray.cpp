#include "VertexArray.h"
#include <iostream>

using namespace cote::graphic;

/**
@throw GlException
*/
cote::graphic::VertexArray::VertexArray(const std::vector<unsigned>& indecies, const VertexAttributeLayout & layout)
{
	unsigned tmpHandler;
	glGenVertexArrays(1, &tmpHandler);
	handler=std::shared_ptr<unsigned>(new unsigned(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
	this->bind();
	m_ebo = std::make_unique<ElementBuffer>();
	m_elemCount = indecies.size();
	m_ebo->setData(m_elemCount, indecies.data());

	m_vbo = std::make_unique<VertexBuffer>(layout);

}

void cote::graphic::VertexArray::bind()const noexcept 
{
	glBindVertexArray(*handler);
}

void cote::graphic::VertexArray::unbind()const noexcept
{
	glBindVertexArray(NULL);
}



void cote::graphic::VertexArray::drawElements()
{
	this->bind();
	glDrawElements(GL_TRIANGLES, m_elemCount, GL_UNSIGNED_INT, NULL);
	this->unbind();
}


