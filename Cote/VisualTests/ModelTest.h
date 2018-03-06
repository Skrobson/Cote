#pragma once
#include "ATest.h"
#include <Light.h>
class ModelTest: public ATest
{
public:
	ModelTest();

	virtual void update();

	~ModelTest();

protected:

	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::shared_ptr<cote::graphic::ShaderProgram> program;
	
	std::shared_ptr<Model> testModel;
	std::shared_ptr<Light> dirLight;
};

