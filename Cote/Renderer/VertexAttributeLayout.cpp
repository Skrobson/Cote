#include "VertexAttributeLayout.h"

using namespace cote::graphic;

void cote::graphic::VertexAttributeLayout::push(VertexAttributeIndex index, unsigned type, unsigned count, unsigned size, bool normalized)
{
	m_attributes.push_back({ (unsigned)index,type,count,m_stride,size });
	m_stride += size;
}
