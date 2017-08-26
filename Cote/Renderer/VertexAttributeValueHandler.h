#pragma once
#include <vector>




namespace cote{
	namespace graphic

{
	class VertexAttributeValueHandler
	{
	public:
		VertexAttributeValueHandler();
		

		~VertexAttributeValueHandler();
	private:
		std::vector<uint8_t> m_values;
	};


}
}
