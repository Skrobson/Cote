#pragma once
#include <memory>
#include "VertexAttributeLayout.h"
#include "ABuffer.h"

namespace cote { namespace graphic
{
	class VertexBuffer:public ABuffer
	{
	public:
		VertexBuffer();

		void bind()const noexcept override;
		void unbind()const noexcept override;



		void setVertexAttributeLayout(const VertexAttributeLayout& layout);
		void copyData(size_t size,const float* data);

		
	};


}
}
