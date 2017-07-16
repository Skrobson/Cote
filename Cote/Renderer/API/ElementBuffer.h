#pragma once
#include <GL\glew.h>
#include <vector>
namespace cote
{namespace graphic 
{
	class ElementBuffer
	{
	public:
		ElementBuffer();
		void bind();
		void unbind();
		void setData(unsigned count, const unsigned* data);

		template<typename RandomIt>
		void setData(RandomIt beg, RandomIt end);
		~ElementBuffer();
	protected:
		unsigned m_handler=0;
	};
	template<typename RandomIt>
	inline void ElementBuffer::setData(RandomIt beg, RandomIt end)
	{
		std::vector elem;
		std::copy(beg, end, elem.begin());
		setData(elem.size(), elem.data());
	}
}
}

