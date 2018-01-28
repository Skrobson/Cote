#pragma once
#include <memory>
#include <GL\glew.h>

namespace cote {
	namespace graphic
	{
		class ABuffer
		{
		public:
			ABuffer();
		
			virtual void bind() const noexcept=0;

			virtual void unbind()const noexcept=0;

			unsigned getHandler()const noexcept { return *handler; }

		protected:
			std::shared_ptr<unsigned> handler;
		};
	}
}

