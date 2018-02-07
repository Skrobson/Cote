#pragma once
#include <vector>
#include <memory>
#include <string>
#include "VertexAttribute.h"


namespace cote {
	namespace graphic {


		class VertexAttributeLayout
		{
		public:
			/**Ustawia wlasciwosci atrybutu, takie jak offset, stride itp,
			*/
			void pushVertexAttribute(std::shared_ptr<VertexAttribute > attribute);

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