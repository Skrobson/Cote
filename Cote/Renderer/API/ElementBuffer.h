#pragma once
#include <GL\glew.h>
namespace cote
{namespace graphic 
{
	class ElementBuffer
	{
	public:
		ElementBuffer();
		void bind();
		void unbind();
		~ElementBuffer();
	protected:
		unsigned m_handler=0;
	};
}
}

