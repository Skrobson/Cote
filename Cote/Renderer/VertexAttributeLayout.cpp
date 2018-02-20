#include "VertexAttributeLayout.h"
#include "GlException.h"
#include <GL\glew.h>

void cote::graphic::VertexAttributeLayout::pushVertexAttribute(std::shared_ptr<VertexAttribute> attribute)
{
	
	auto tmpAttribute = std::make_pair(attribute, size);
	attributes.push_back(tmpAttribute);
	size += attribute->getSize();
}


