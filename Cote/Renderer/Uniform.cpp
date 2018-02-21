#include "Uniform.h"

using namespace cote::graphic;

cote::graphic::Uniform::Uniform(std::string name): uniformName(name)
{
}

void Uniform::searchForUniformLocation(std::shared_ptr<const ShaderProgram> program)
{
	auto location = glGetUniformLocation(program->getProgramID(), uniformName.c_str());
	uniformLocations.insert_or_assign(program, location);
}

bool cote::graphic::Comparator::operator()(std::shared_ptr<const ShaderProgram> a, std::shared_ptr<const ShaderProgram> b)const
{
	return a->getProgramID() > b->getProgramID();
}
//template<typename T>
//void UniformT::updateValueForProgram(const std::shared_ptr<ShaderProgram>  program)
//{
//	auto loc = uniformLocations.find(program);
//	if (loc != uniformLocations.end())
//		program->setUniform(loc->second, 0);
//}

//void cote::graphic::UniformT::updateValueForProgram(const std::shared_ptr<ShaderProgram> program)
//{
//	auto loc = uniformLocations.find(program);
//	if (loc != uniformLocations.end())
//		program->setUniform(loc->second, 0);
//}
