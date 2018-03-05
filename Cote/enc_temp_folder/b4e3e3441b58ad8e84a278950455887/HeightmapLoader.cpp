#include "HeightmapLoader.h"
#include <algorithm>
#include <iterator>
#include <GlobalLogger.h>

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

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t z = 0; z < height; ++z)
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

	for (size_t x = 0; x <(width - 1); ++x)
	{
		if (x % 2 == 0)
		{
			for (size_t z = 0; (z + 1) < height; ++z)
			{
				indicies.push_back(z + x * height);
				indicies.push_back((z + x * height) + height);
			}
		}
		else
		{
			for (size_t z =height -1 ; z  >height; --z)
			{
				indicies.push_back(z + x * height);
				indicies.push_back((z + x * height) - height);

			}
		}
		
	}
	this->indicies = std::move(indicies);
}
