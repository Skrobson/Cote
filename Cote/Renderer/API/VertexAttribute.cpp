#include "VertexAttribute.h"

using namespace cote::graphic;

bool VertexAttribute::operator<(const VertexAttribute & other)
{
	return (this->m_index<other.m_index);
}

bool VertexAttribute::operator>(const VertexAttribute & other)
{
	return (this->m_index<other.m_index);
}

bool VertexAttribute::operator==(const VertexAttribute & other)
{
	return (this->m_index == other.m_index);
}
