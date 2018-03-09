
#include "ShaderProgram.h"
#include "GlException.h"
#include "GLerror.h"
#include <gtc/type_ptr.hpp>

using namespace cote::graphic;



ShaderProgram::ShaderProgram()
{
	createProgram();
}

ShaderProgram::ShaderProgram(std::initializer_list<const Shader> list)
{
	createProgram();
	for (auto& shader : list)
	{
		attachShader(shader);
	}
	linkProgram();
}


void ShaderProgram::attachShader(const Shader& shader)
{
	if (!shader.isCompiled()) 
	{
		throw GlException("Shader not compiled");
	}
	glAttachShader(*programID, shader.getShaderID());
	attachedShaders.push_back(shader.getShaderID());

	
}

void ShaderProgram::linkProgram()
{
	glLinkProgram(*programID);

	GLint success;
	char errBuffer[512];
	glGetProgramiv(*programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*programID, sizeof(errBuffer), NULL, errBuffer);
		std::string error("Failed to link shader program ");
		error += errBuffer;
		throw GlException(error);
		
	}
	for (auto& shader : this->attachedShaders)
	{
		glDetachShader(*programID, shader);
	}
	attachedShaders.clear();
	linked = true;
	attachedShaders.shrink_to_fit();

	setUpUniformLocations();
}

void ShaderProgram::bind()const
{

	glUseProgram(*programID);
}

void ShaderProgram::unbind()const
{
	glUseProgram(NULL);
}

//void cote::graphic::ShaderProgram::setUniform(const std::string & name, int value)
//{
//	auto location = uniformLocations.find(name);
//	if (location != uniformLocations.end())
//		setUniform(location->second, value);
//	else
//		searchForUniformLocation(name);
//}

void cote::graphic::ShaderProgram::setUniform(int location, int value)
{
	glUniform1i(location, value);
}

void cote::graphic::ShaderProgram::setUniform(int location, unsigned value)
{
	glUniform1ui(location, value);
}

void cote::graphic::ShaderProgram::setUniform(int location, float value)
{
	glUniform1f(location, value);
}

void cote::graphic::ShaderProgram::setUniform(int location, glm::vec2 value)
{
	glUniform2fv(location, 1, glm::value_ptr(value));
}

void cote::graphic::ShaderProgram::setUniform(int location, glm::vec3 value)
{
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void cote::graphic::ShaderProgram::setUniform(int location, glm::vec4 value)
{
	glUniform4fv(location, 1, glm::value_ptr(value));
}

void cote::graphic::ShaderProgram::setUniform(int location, glm::mat3 value)
{
	glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
}

void cote::graphic::ShaderProgram::setUniform(int location, glm::mat4 value)
{
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void cote::graphic::ShaderProgram::setUpUniformLocations()
{
	bind();
	GLint numActiveUniforms = 0;
	glGetProgramiv(*programID, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

	std::vector<GLchar> nameData(256);
	std::vector<GLenum> properties;

	const auto buffSize = 256;
	auto length = 0;
	char name[buffSize];
	GLint size;
	GLenum type;
	for (int attrib = 0; attrib < numActiveUniforms; ++attrib)
	{
		glGetActiveUniform(*programID, (GLuint)attrib, buffSize, &length,&size, &type, name);
		
		uniformLocations.insert(std::make_pair(name, attrib));
	}
	unbind();
}

void cote::graphic::ShaderProgram::searchForUniformLocation(std::string uniformName)
{
	auto location = glGetUniformLocation(*programID, uniformName.c_str());
	if(location >=0)
	uniformLocations.insert_or_assign(uniformName, location);
}

void cote::graphic::ShaderProgram::createProgram()
{
	programID = std::shared_ptr<unsigned>(new unsigned(glCreateProgram()), [](unsigned* program){
		
		glDeleteProgram(*program);
		delete program;
	});
	
}
