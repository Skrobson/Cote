#pragma once
#include <glm.hpp>
#include <vector>
#include <memory>
#include <utility>


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
			unsigned getIndex()const { return m_index; }
			size_t getCount() const { return m_count; }
			size_t getSize()const{ return m_size; }

			const float* getRawData()const { return m_data.data(); }
			virtual ~VertexAttribute(){}
		protected:

			VertexAttribute(){}
			unsigned m_index; 
			size_t m_count; //gl need sizeOf( count of variables)
			size_t m_size;
			std::vector<float> m_data;
			
			
			
			
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
		protected:
			//std::vector<glm::vec2> m_originalData;
			virtual void convertData(const std::vector<glm::vec2>& data) override;
		};

		class VertexAttribute3f :public VertexAttributeT<glm::vec3>
		{
		public:
			VertexAttribute3f(VertexAttributeIndex index , const std::vector<glm::vec3>& data);
			VertexAttribute3f(unsigned index , const std::vector<glm::vec3>& data);
		protected:
			//std::vector<glm::vec3> m_originalData;
			virtual void convertData(const std::vector<glm::vec3>& data)override;
		};




		class VertexAttributeLayout
		{
		public:
			/**Ustawia wlasciwosci atrybutu, takie jak offset, stride itp,
			*only for floats
				  */
			
			void pushVertexAttribute(std::shared_ptr<VertexAttribute > attribute);

			const std::vector<std::pair <std::shared_ptr<VertexAttribute>, unsigned>>& getAttributes()const { return m_attributes; }
			
			size_t getSizeOf() const
			{
				return m_size;
			}
		protected:
			std::vector<std::pair <std::shared_ptr<VertexAttribute> , size_t>> m_attributes;
			size_t m_size=0;

			
		};






	}

}