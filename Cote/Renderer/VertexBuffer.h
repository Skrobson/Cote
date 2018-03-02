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
			/**
			* @throws GlException
			*/
			VertexBuffer(const VertexAttributeLayout& layout);
			VertexBuffer() = delete;
			void bind()const noexcept override;
			void unbind()const noexcept override;


		private:
			/**
			 * @throws GlException
			 */
			void setVertexAttributeLayout(const VertexAttributeLayout& layout);
		};
	}
}
