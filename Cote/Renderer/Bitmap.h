#pragma once
#include <vector>
#include <FreeImage.h>
#include <memory>

namespace cote
{
	namespace graphic
	{
		class Bitmap
		{
		public:
			Bitmap(std::string filePath);

			const unsigned char* getRawData()const;

			const size_t getHeight()const noexcept 
			{
				return height; 
			}


			const size_t getWidth()const noexcept
			{
				return width;
			}


		private:
			size_t height, width;

			std::unique_ptr<FIBITMAP> bitmap;
			

			
		};
	}
}

