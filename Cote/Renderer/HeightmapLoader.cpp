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
	auto bits = bitmap.getRawData(); 
	auto height = bitmap.getHeight();
	auto width = bitmap.getWidth();

	//std::vector<float> attidutes;
	//std::copy(bits, bits + (height * width), std::back_inserter(attidutes));

	std::vector<glm::vec3> vertices;

	for (size_t z = 0; z < height; ++z)
	{
		for (size_t x = 0; x < width; ++x)
		{
			float px = static_cast<float>(x);
			float py = 0.0f;//static_cast<float>(bits[x + z]);
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
		if (z % 2 == 0)
		{
			size_t x;
			for ( x= 0; x < width; ++x)
			{
				indicies.push_back(x +( z * width));
				indicies.push_back((x + (z * width)) + width);
				
			}
			if (z != height - 2)
			{
				indicies.push_back(--x + (z* width));
			}
		}
		else
		{
			size_t x;
			for ( x= width -1 ; x  >width; --x)
			{
				indicies.push_back(x + z * width);
				indicies.push_back((x + z * width) - width);

			}
			if (z != height - 2)
			{
				indicies.push_back(++x + (z* width));
			}
		}
		
	}
	this->indicies = std::move(indicies);
}
