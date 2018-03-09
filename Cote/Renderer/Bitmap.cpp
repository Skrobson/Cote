#include "Bitmap.h"

using namespace cote::graphic;

Bitmap::Bitmap(const std::string& filePath)
{
	load(filePath);
}

cote::graphic::Bitmap::Bitmap()
{
	
}

void cote::graphic::Bitmap::load(const std::string & filePath)
{
	auto unloadBitmap = [](FIBITMAP* bitmap) {
		FreeImage_Unload(bitmap);
	};

	FIBITMAP * data = FreeImage_Load(FreeImage_GetFIFFromFilename(filePath.c_str()), filePath.c_str());
	bitmap = std::unique_ptr<FIBITMAP, std::function<void(FIBITMAP*)>>(FreeImage_ConvertTo32Bits(data), unloadBitmap);

	width = FreeImage_GetWidth(bitmap.get());
	height = FreeImage_GetHeight(bitmap.get());
	unloadBitmap(data);
	
}


const unsigned char* cote::graphic::Bitmap::getRawData() const
{
	return FreeImage_GetBits(bitmap.get());
}

std::vector<glm::vec3> cote::graphic::Bitmap::getColors() const
{
	RGBQUAD color;
	std::vector<glm::vec3> colors;
	for (size_t y= 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			FreeImage_GetPixelColor(bitmap.get(), x, y, &color);
			glm::vec3 colorVec = { color.rgbRed,color.rgbGreen, color.rgbBlue };
			colors.push_back(std::move(colorVec));
		}
	}
	return colors;
}
