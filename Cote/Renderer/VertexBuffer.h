#pragma once
#include <memory>
#include "VertexAttributeLayout.h"
#include "ABuffer.h"

namespace cote 
{ namespace graphic
	{
		class VertexBuffer:public ABuffer
		{
		public:
			VertexBuffer(const VertexAttributeLayout& layout);
			VertexBuffer() = delete;
			void bind()const noexcept override;
			void unbind()const noexcept override;


		private:
			void setVertexAttributeLayout(const VertexAttributeLayout& layout);
		};
	}
}
