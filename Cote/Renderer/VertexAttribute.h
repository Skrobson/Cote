#pragma once
#include <glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include <GL\glew.h>

namespace cote {
	namespace graphic {



		enum  VertexAttributeIndex :unsigned {
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

			void setName(const std::string& attribName) { attributeName = attribName; }

			std::string getName()const { return attributeName; }

			void setIndex(int index) { this->index = index; }

			unsigned getIndex()const { return index; }

			size_t getCount() const { return count; }

			size_t getSize()const { return size; }

			GLenum getType()const { return dataType; }

			virtual const void* getRawData()const = 0;

			virtual ~VertexAttribute() {}

		protected:

			VertexAttribute(const GLenum dataType);

			unsigned index;

			size_t count;

			size_t size;

			const GLenum dataType;

			std::string attributeName;
		};

		template<typename T, typename S>
		class VertexAttributeT :public VertexAttribute
		{
		public:


			virtual const void* getRawData()const override { return data.data(); }

		protected:
			VertexAttributeT(GLenum dataType) :VertexAttribute(dataType) {}

			virtual void convertData(const std::vector<T>& data) = 0;

			std::vector<S> data;
		};

		template<typename T>
		class VertexAttributeF : public VertexAttributeT<T, float>
		{
		protected:
			VertexAttributeF() :VertexAttributeT(GL_FLOAT) {}

			virtual void convertData(const std::vector<T>& data) = 0;
		};

		class VertexAttribute2f :public VertexAttributeF<glm::vec2>
		{
		public:
			VertexAttribute2f(VertexAttributeIndex index, const std::vector<glm::vec2>& data);

			VertexAttribute2f(unsigned index, const std::vector<glm::vec2>& data);

		protected:
			VertexAttribute2f(const std::vector<glm::vec2>& data);

			virtual void convertData(const std::vector<glm::vec2>& data) override;
		};



		class VertexAttribute3f :public VertexAttributeF<glm::vec3>
		{
		public:

			VertexAttribute3f(VertexAttributeIndex index, const std::vector<glm::vec3>& data);

			VertexAttribute3f(unsigned index, const std::vector<glm::vec3>& data);

		protected:
			VertexAttribute3f(const std::vector<glm::vec3>& data);

			virtual void convertData(const std::vector<glm::vec3>& data)override;
		};
	}
}