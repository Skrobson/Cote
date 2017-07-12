#pragma once
#include <GL\glew.h>
#include <glm.hpp>

namespace cote {
	namespace graphic {

		enum  VertexAttributeLayout {
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
			bool normalized;
			virtual const float* getValuePtr() const = 0;
			//	const GLint& getIndex()const;
			//	const size_t& getSize()const;
			//	const size_t& getCount() const;
			//	const bool& normalized() const;

			//TODO:: nie wiem czy beda potrzebne te operatory, mozliwe ze nie trzeba ich podawac po kolei ( sprawdziæ)
			bool operator < (const VertexAttribute& other);
			bool operator > (const VertexAttribute& other);
			bool operator == (const VertexAttribute& other);

		protected:
			GLint m_index; //VertexAttributeLayout
			size_t size;
			size_t count;
		};

		class VertexAttributeF : public VertexAttribute
		{
		public:
			VertexAttributeF() = delete;
			//	VertexAttributeF(const float& value);

		protected:
			float m_value;
		};

}

}