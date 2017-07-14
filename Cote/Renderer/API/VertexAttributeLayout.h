#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <vector>
#include <type_traits>

namespace cote {
	namespace graphic {

		enum  VertexAttributeIndex {
			POSITION = 0,
			UV_0,
			NORMAL,
			COLOR_0,
			BITANGES,
			TANGENT,
			UV_1,
			COLOR_1,


			MAX_VERTEX_LAYOUT = 16
		};

		class VertexAttribute
		{
		public:
			
			uint16_t m_index; 
			uint16_t m_type; 
			uint16_t m_count; //gl need sizeOf( count of variables)
			uint16_t m_offset;
			uint16_t m_size;
			bool m_normalized;
		};


		class VertexAttributeLayout
		{
		public:
			template<typename T>
			void pushVertexAttribute(T t, VertexAttributeIndex index,bool normalized);
			const std::vector<VertexAttribute>& getAttributes()const { return m_attributes; }

			uint16_t getStride() const
			{
				return m_stride;
			}
		protected:
			std::vector<VertexAttribute> m_attributes;
			uint16_t m_stride=0;

			void push(VertexAttributeIndex index, uint16_t type, uint16_t count, uint16_t size, bool normalized);
		};




		template<typename T>
		inline void VertexAttributeLayout::pushVertexAttribute(T t, VertexAttributeIndex index, bool normalized)
		{
			uint16_t size = sizeof(t);
			uint16_t count = size / sizeof(float);
			push(index, GL_FLOAT, count, size, normalized);
		}
	}

}