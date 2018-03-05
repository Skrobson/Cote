#pragma once
#include "ATest.h"
#include "ModelTest.h"
class MapTest : public ModelTest
{
public:
	MapTest();

	//virtual void update() override;

private:
	cote::graphic::Shader vS;
	cote::graphic::Shader fS;
	std::shared_ptr<cote::graphic::ShaderProgram> program;

	std::shared_ptr<Model> testModel;
};

