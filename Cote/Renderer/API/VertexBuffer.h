#pragma once
#include <memory>
#include "VertexAttributeLayout.h"

namespace cote { namespace graphic
{
	class VertexBuffer
	{
	public:
		VertexBuffer();

		void bind();
		void unbind();
		void setVertexAttributeLayout(const VertexAttributeLayout& layout);
		void setData(uint16_t size, float* data);
		~VertexBuffer();
	protected:

		unsigned m_handler=0;
		std::shared_ptr<VertexAttributeLayout> m_layout;
	};
}
}
