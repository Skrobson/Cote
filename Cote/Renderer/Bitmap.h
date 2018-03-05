#pragma once
#include <vector>
#include <FreeImage.h>
#include <memory>
#include <functional>
#include <glm.hpp>

namespace cote
{
	namespace graphic
	{
		class Bitmap
		{
		public:
			Bitmap(const std::string& filePath);
			Bitmap();

			void load(const std::string& filePath);

			const unsigned char* getRawData()const;

			std::vector<std::vector<glm::vec3>> getColors()const ;

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

			std::unique_ptr<FIBITMAP, std::function<void(FIBITMAP*)>> bitmap;
		};
	}
}

