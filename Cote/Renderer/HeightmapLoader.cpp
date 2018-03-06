#include "HeightmapLoader.h"
#include <algorithm>
#include <iterator>
//#include <GlobalLogger.h>

using namespace cote;

HeightmapLoader::HeightmapLoader()
{
}


HeightmapLoader::~HeightmapLoader()
{
}

void cote::HeightmapLoader::convert(const Bitmap & bitmap)
{
	auto bits = bitmap.getColors(); 
	auto height = bitmap.getHeight();
	auto width = bitmap.getWidth();
	//size_t height = 5;
	//size_t width = 5;

	//std::vector<float> attidutes;
	//std::copy(bits, bits + (height * width), std::back_inserter(attidutes));

	std::vector<glm::vec3> vertices;

	for (size_t z = 0; z < height; ++z)
	{
		for (size_t x = 0; x < width; ++x)
		{
			
			float px = static_cast<float>(x);
			float py = static_cast<float>(grayscale( bits[x + (z* height)]));//static_cast<float>(bits[x + z]); 0.0f;
			float pz = static_cast<float>( z);

			//DEBUG_LOG(bits[x + z]);

			glm::vec3 pos = { px ,py, pz  };
			vertices.push_back(std::move(pos));
		}

	}
	this->vertices = std::move(vertices);

	std::vector<unsigned> indicies;

	for (size_t z = 0; z <height -1; ++z)
	{
	//	if ((z % 2) == 0)
		{
			size_t x;
			for ( x= 0; x < width -1; ++x)
			{

				indicies.push_back(x + width + (z*width));
				indicies.push_back(x + 1 + (z*width));
				indicies.push_back(x + (z*width));

				indicies.push_back(x + width + (z*width));
				indicies.push_back(x + 1 + width + (z*width));
				indicies.push_back(x + 1 + (z*width));
				
			}
	
		}
		//else
		//{
		//	size_t x;
		//	for ( x = (width-1)  ; x  > 0 ; --x)
		//	{
		//		indicies.push_back(x + width + (z*width));
		//		indicies.push_back(x + (z*width) - 1);
		//		indicies.push_back(x + (z*width));

		//		indicies.push_back(x + width + (z*width));
		//		indicies.push_back(x  +width +(z*width) - 1 );
		//		indicies.push_back(x + (z*width) - 1);
		//	}
		//}
		
	}
	this->indicies = std::move(indicies);
}

float cote::HeightmapLoader::grayscale(const glm::vec3 & color)
{
	//float rGamma = 0.1f;
	//float gGamma = 0.2f;
	//float bGamma = 0.3f;

	auto gray = (color.r + color.g + color.b) / 3;

	return gray;
}
