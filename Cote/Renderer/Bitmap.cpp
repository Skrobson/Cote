#include "Bitmap.h"

using namespace cote::graphic;

Bitmap::Bitmap(std::string filePath)
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
