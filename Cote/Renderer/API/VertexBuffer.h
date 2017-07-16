#pragma once
#include <memory>
#include "VertexAttributeLayout.h"

namespace cote { namespace graphic
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(VertexBuffer&& )=delete;
		VertexBuffer(VertexBuffer&) = delete;
		void bind();
		void unbind();



		void setVertexAttributeLayout(const VertexAttributeLayout& layout);
		void setData(size_t size,const uint8_t* data);

		unsigned getHandler()const { return m_handler; }
		~VertexBuffer();
	protected:

		unsigned m_handler=0;
		
	};


}
}
