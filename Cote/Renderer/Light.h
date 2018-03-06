#pragma once
#include <glm.hpp>
#include "Uniform.h"
namespace cote
{
	using namespace cote::graphic;
	class Light
	{
	public:
		Light();
	
		
		UniformT<glm::vec3> direction;
	
		UniformT<glm::vec3> ambient;
		UniformT<glm::vec3> diffuse;
		UniformT<glm::vec3> specular;
		virtual ~Light();
	};
}

