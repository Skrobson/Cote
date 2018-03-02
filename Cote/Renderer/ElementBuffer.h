#pragma once
#include <GL\glew.h>
#include <vector>
#include <memory>
#include "ABuffer.h"
namespace cote
{
	namespace graphic 
	{
		class ElementBuffer :public ABuffer
		{
		public:
			ElementBuffer();

			void bind()const noexcept override;
			void unbind()const noexcept override;

			void setData(size_t count, const unsigned* data);
		};
	}
}

