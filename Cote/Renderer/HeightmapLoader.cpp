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

	auto indexCount = this->indicies.size();
	normals.reserve((this->vertices.size()));
	normals.resize(this->vertices.size());
	

	for (int i = 0; i < indexCount , i+3< indexCount; i += 3)
	{
		// get the three vertices that make the faces
		glm::vec3 p0 = this->vertices[indicies[i + 0]];
		glm::vec3 p1 = this->vertices[indicies[i + 1]];
		glm::vec3 p2 = this->vertices[indicies[i + 2]];

		glm::vec3 e1 = p1 - p0;
		glm::vec3 e2 = p2 - p0;
		glm::vec3 normal = glm::cross(e1, e2);
		normal = glm::normalize(normal);

		normals[indicies[i + 0]] += normal;
		normals[indicies[i + 1]] += normal;
		normals[indicies[i + 2]] += normal;
	}
	for (auto & norm : normals)
	{
		norm = glm::normalize(norm);
	}
}

float cote::HeightmapLoader::grayscale(const glm::vec3 & color)
{
	auto gray = (color.r + color.g + color.b) / 3;

	return gray;
}
