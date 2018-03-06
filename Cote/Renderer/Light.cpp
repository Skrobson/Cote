#include "Light.h"


using namespace cote::graphic;
using namespace cote;
Light::Light()
{
	ambient.setUniformName("light.ambient");
	diffuse.setUniformName("light.diffuse");
	direction.setUniformName("light.direction");
	specular.setUniformName("light.specular");

}


Light::~Light()
{
}
