#pragma once
#include <vector>


namespace cote
{
	namespace graphic
	{
		class Image
		{
		public:
			Image();
			~Image();

		private:
			size_t x, y;

			std::vector<unsigned char> bytes;
		};
	}
}

