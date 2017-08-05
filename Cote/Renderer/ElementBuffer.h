#pragma once
#include <GL\glew.h>
#include <vector>
#include <memory>
#include "ABuffer.h"
namespace cote
{namespace graphic 
{
	class ElementBuffer:public ABuffer
	{
	public:
		ElementBuffer();

		void bind()const noexcept override;
		void unbind()const noexcept override;
		
		void copyData(size_t count, const unsigned* data)noexcept;
		
		template<typename RandomIt>
		void setData(RandomIt beg, RandomIt end)noexcept;
	};



	template<typename RandomIt>
	inline void ElementBuffer::setData(RandomIt beg, RandomIt end)noexcept
	{
		std::vector elem;
		std::copy(beg, end, elem.begin());
		copyData(elem.size(), elem.data());
	}
}
}

