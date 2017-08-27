#include "VertexBuffer.h"
#include <iostream>
using namespace cote::graphic;

void cote::graphic::VertexBuffer::bind()const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, *m_handler);
}

void cote::graphic::VertexBuffer::unbind()const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

cote::graphic::VertexBuffer::VertexBuffer(const VertexAttributeLayout & layout)
{
	unsigned* tmpHandler = new unsigned;
	glGenBuffers(1, tmpHandler);
	m_handler = std::shared_ptr<unsigned>(std::move(tmpHandler), [](unsigned* handler) {
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
	glBufferData(GL_ARRAY_BUFFER, layout.getSizeOf(), NULL, GL_STATIC_DRAW);
	//GLenum error = glGetError();
	//if (error != GL_NO_ERROR)
	//{
	//	std::cerr << "after creating buffer " << glewGetErrorString(error);
	//}
	for (auto &a : attributes)
	{
		auto attribute = a.first;
		glEnableVertexAttribArray(attribute->getIndex());
		//GLenum error = glGetError();
		//if (error != GL_NO_ERROR)
		//{
		//	std::cerr << "after enable vertexAttribArray " << glewGetErrorString(error);
		//}
		//dla wartosci podawanych pokolei przy pomocy subData
	
		glBufferSubData(GL_ARRAY_BUFFER, offset, attribute->getSize(), attribute->getRawData());
		// error = glGetError();
		//if (error != GL_NO_ERROR)
		//{
		//	std::cerr << "after sub data " << glewGetErrorString(error);
		//}
		
		glVertexAttribPointer(attribute->getIndex(), attribute->getCount(), GL_FLOAT, GL_FALSE, 0, (GLvoid*)a.second);

		//error = glGetError();
		//if (error != GL_NO_ERROR)
		//{
		//	std::cerr << "after Vertex Attrib Pointer " << glewGetErrorString(error);
		//}
		
		//dla wymieszanych wartosci
		//glVertexAttribPointer(a.m_index, a.m_count, GL_FLOAT, GL_FALSE, layout.getStride() , (GLvoid*)a.m_offset);
		offset += attribute->getSize();
	}

}


//void cote::graphic::VertexBuffer::copyData(size_t size , const float* data)
//{
//	this->bind();
//	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
//}


