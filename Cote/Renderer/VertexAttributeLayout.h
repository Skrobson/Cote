#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <vector>
#include <type_traits>
#include <cassert>

namespace cote {
	namespace graphic {

		enum  VertexAttributeIndex :unsigned{
			POSITION =  0,
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
			
			unsigned m_index; 
			unsigned m_type; 
			unsigned m_count; //gl need sizeOf( count of variables)
			unsigned m_offset;
			unsigned m_size;
			bool m_normalized;
		};


		class VertexAttributeLayout
		{
		public:
			/**Ustawia wlasciwosci atrybutu, takie jak offset, stride itp,
			*only for floats
				  */
			template<typename T>
			void pushVertexAttribute(VertexAttributeIndex index, bool normalized);

			void pushVertexAttribute(VertexAttributeIndex index, unsigned type, unsigned count, unsigned size, bool normalized);

			const std::vector<VertexAttribute>& getAttributes()const { return m_attributes; }
			
			unsigned getStride() const
			{
				return m_stride;
			}
		protected:
			std::vector<VertexAttribute> m_attributes;
			unsigned m_stride=0;

			void pushVertexAttribute(VertexAttributeIndex index, unsigned type, unsigned count, unsigned size, bool normalized);
		};




		template<typename T>
		inline void VertexAttributeLayout::pushVertexAttribute(VertexAttributeIndex index, bool normalized)
		{
			size_t size = sizeof(T);
			size_t count = size / sizeof(float);
		
			pushVertexAttribute(index, GlType, count, size, normalized);
		}
	}

}