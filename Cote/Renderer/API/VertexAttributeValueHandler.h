#pragma once
#include <vector>




namespace cote{
	namespace graphic

{
	class VertexAttributeValueHandler
	{
	public:
		VertexAttributeValueHandler();
		const uint8_t* getValues()const { return m_values.data(); }
		template<typename Value>
		void pushAttributeValue(Value v);

		~VertexAttributeValueHandler();
	private:
		std::vector<uint8_t> m_values;
	};

	template<typename Value>
	inline void VertexAttributeValueHandler::pushAttributeValue(Value v)
	{
		constexpr size_t vSize = sizeof(v);
		uint8_t[vSize] v8 = static_cast<uint8_t>(v);
		for (auto i = 0; i < vSize; ++i)
		{
			m_values.push_back(v8[i]);
		}
	}
}
}
