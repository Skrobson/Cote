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
				*narazie wspierane sa typy GL_FLOAT i GL_BYTE  */
			template<typename T>
			void pushVertexAttribute(VertexAttributeIndex index, unsigned GlType, bool normalized);
			const std::vector<VertexAttribute>& getAttributes()const { return m_attributes; }
			
			unsigned getStride() const
			{
				return m_stride;
			}
		protected:
			std::vector<VertexAttribute> m_attributes;
			unsigned m_stride=0;

			void push(VertexAttributeIndex index, unsigned type, unsigned count, unsigned size, bool normalized);
		};




		template<typename T>
		inline void VertexAttributeLayout::pushVertexAttribute(VertexAttributeIndex index,unsigned GlType, bool normalized)
		{
			size_t size = sizeof(T);
			size_t count;
			switch(GlType):
				case GL_FLOAT:
					count = size / sizeof(float);
					break;
				case GL_BYTE:
					count = size / sizeof(uint8_t);
					break;
				default:
					static_assert(false, "Type is not supported");


			push(index, GlType, count, size, normalized);
		}
	}

}