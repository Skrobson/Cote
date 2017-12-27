#pragma once
#include <glm.hpp>
#include <vector>
#include <memory>
#include <string>


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
			unsigned getIndex()const { return index; }
			size_t getCount() const { return count; }
			size_t getSize()const{ return size; }

			void findIndex(const unsigned programHandler) throw (GlException);
			const float* getRawData()const { return data.data(); }
			virtual ~VertexAttribute(){}

		protected:

			VertexAttribute(){}

			

			unsigned index;
			size_t count; 
			size_t size;
			std::vector<float> data;
			std::string attributeName;
		};
	
		template<typename T>
		class VertexAttributeT :public VertexAttribute
		{
		protected:
			//std::vector<T> m_originalData;
			virtual void convertData(const std::vector<T>& data) = 0;
		};



		class VertexAttribute2f :public VertexAttributeT<glm::vec2>
		{
		public:
			VertexAttribute2f(VertexAttributeIndex index,const std::vector<glm::vec2>& data);

			VertexAttribute2f(unsigned index, const std::vector<glm::vec2>& data);

			VertexAttribute2f(const std::string& attribName, const std::vector<glm::vec2>& data);

		protected:
			VertexAttribute2f(const std::vector<glm::vec2>& data);

			virtual void convertData(const std::vector<glm::vec2>& data) override;
		};



		class VertexAttribute3f :public VertexAttributeT<glm::vec3>
		{
		public:

			VertexAttribute3f(VertexAttributeIndex index , const std::vector<glm::vec3>& data);

			VertexAttribute3f(unsigned index , const std::vector<glm::vec3>& data);

			VertexAttribute3f(const std::string& attribName, const std::vector<glm::vec3>& data);

		protected:
			VertexAttribute3f(const std::vector<glm::vec3>& data);
			
			virtual void convertData(const std::vector<glm::vec3>& data)override;
		};




		class VertexAttributeLayout
		{
		public:
			/**Ustawia wlasciwosci atrybutu, takie jak offset, stride itp,
			*only for floats*/
			void pushVertexAttribute(std::shared_ptr<VertexAttribute > attribute);

			/**Wyszukuje indexy atrybutow w podanym shader programie
			* Rzuca wyj¹tek GlException
			*/
			void findVertexAttributeIndecies(const unsigned shaderProgramHandler)throw (GlException);

			/**return pair attribute and offset*/
			const std::vector<std::pair <std::shared_ptr<VertexAttribute>, unsigned>>& getAttributes()const 
			{ 
				return attributes;
			}
			
			size_t getSizeOf() const
			{
				return size;
			}

		protected:

			std::vector<std::pair <std::shared_ptr<VertexAttribute> , size_t>> attributes;
			size_t size=0;
		};






	}

}