#include "Light.h"


using namespace cote::graphic;
using namespace cote;
Light::Light()
{
	ambient.setUniformName("directionalLight.ambient");
	diffuse.setUniformName("directionalLight.diffuse");
	direction.setUniformName("directionalLight.direction");
	specular.setUniformName("directionalLight.specular");

}


Light::~Light()
{
}
