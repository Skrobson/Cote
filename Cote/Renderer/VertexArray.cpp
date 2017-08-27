#include "VertexArray.h"
#include <iostream>

using namespace cote::graphic;

cote::graphic::VertexArray::VertexArray(const std::vector<unsigned>& indecies, const VertexAttributeLayout & layout)
{
	unsigned tmpHandler;
	glGenVertexArrays(1, &tmpHandler);
	m_handler=std::shared_ptr<unsigned>(new unsigned(tmpHandler), [](unsigned* handler) {
		glDeleteBuffers(1, handler);
		delete handler;
	});
	this->bind();
	m_ebo = std::make_unique<ElementBuffer>();
	m_elemCount = indecies.size();
	m_ebo->copyData(m_elemCount, indecies.data());

	//GLenum error = glGetError();
	//if (error != GL_NO_ERROR)
	//{
	//	std::cerr<<"after ebo " << glewGetErrorString(error);
	//}
	m_vbo = std::make_unique<VertexBuffer>(layout);
	//error = glGetError();
	//if (error != GL_NO_ERROR)
	//{
	//	std::cerr << "after vbo " << glewGetErrorString(error);
	//}
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

void cote::graphic::VertexArray::drawElements()
{
	this->bind();
	glDrawElements(GL_TRIANGLES, m_elemCount, GL_UNSIGNED_INT, NULL);
	//for separate arrays 
	//glDrawArrays(GL_TRIANGLES ,0, m_elemCount);
	this->unbind();
}


