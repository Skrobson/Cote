#include "ElementBuffer.h"

using namespace cote::graphic;

ElementBuffer::ElementBuffer()
{
	glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_handler);
}


ElementBuffer::~ElementBuffer()
{
}
