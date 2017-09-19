#pragma once

//#include <memory>
//#include <vector>
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexAttributeLayout.h"

namespace cote
{
	namespace graphic
	{
		class VertexArray :public ABuffer
		{
		public:
			VertexArray() = delete;

			VertexArray(const std::vector<unsigned>& indecies, const VertexAttributeLayout & layout);

			void bind()const noexcept override;
			void unbind()const noexcept override;

			size_t getElemCount()const { return m_elemCount; }

			//void copyElements(size_t count, const unsigned* data);

			void drawElements();

		protected:
			std::unique_ptr<VertexBuffer> m_vbo;
			std::unique_ptr<ElementBuffer> m_ebo;
			size_t m_elemCount;

		};
	}
}