#pragma once
#include "Bitmap.h"
#include "Mesh.h"


namespace cote
{
	using namespace cote::graphic;
	class HeightmapLoader
	{
	public:
		HeightmapLoader();
	
		~HeightmapLoader();

		void convert(const Bitmap & bitmap );

		std::vector<glm::vec3> vertices;
		std::vector<unsigned> indicies;
	private:

	
	};
}

