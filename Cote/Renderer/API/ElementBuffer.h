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
		ElementBuffer(ElementBuffer&) = delete;
		ElementBuffer(ElementBuffer&& )=delete;
		void bind();
		void unbind();
		unsigned getHandler()const { return m_handler; }

		void setData(size_t count, const unsigned* data);
		
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

