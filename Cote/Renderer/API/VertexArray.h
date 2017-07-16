#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexAttributeLayout.h"
#include <memory>

namespace cote
{
	namespace graphic
	{
		class VertexArray
		{
		public:
			VertexArray();
			
			VertexArray(VertexArray&&) = delete;
			VertexArray(VertexArray&) = delete;
			
			void bind();
			void unbind();
			unsigned getHandler()const { return m_handler; }
			size_t getElemCount()const { return m_elemCount; }

			void copyElements(size_t count, const unsigned* data);
			template<typename RandomIt>
			void copyElements(RandomIt beg, RandomIt end);
			void setLayout(const VertexAttributeLayout& layout);
			void setAttributesValues(size_t count, const uint8_t* data);
			void drawElements();
			~VertexArray();
		protected:
			std::unique_ptr<VertexBuffer> m_vbo;
			std::unique_ptr<ElementBuffer> m_ebo;
			unsigned m_handler=0;
			size_t m_elemCount;

		};



		template<typename RandomIt>
		inline void VertexArray::copyElements(RandomIt beg, RandomIt end)
		{
			m_ebo->copyData(beg, end);
		}

	}
}

