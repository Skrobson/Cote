#include "VertexAttributeLayout.h"

using namespace cote::graphic;

void cote::graphic::VertexAttributeLayout::push(VertexAttributeIndex index, uint16_t type, uint16_t count, uint16_t size, bool normalized)
{
	m_attributes.push_back({ index,type,count,m_stride,size });
	m_stride += size*count;
}
