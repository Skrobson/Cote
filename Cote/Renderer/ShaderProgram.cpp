#include "ShaderProgram.h"
#include "GlException.h"
#include "GLerror.h"

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
}

void ShaderProgram::bind()const
{

	glUseProgram(*programID);
}

void ShaderProgram::unbind()const
{
	glUseProgram(NULL);
}



void cote::graphic::ShaderProgram::createProgram()
{
	programID = std::shared_ptr<unsigned>(new unsigned(glCreateProgram()), [](unsigned* program){
		
		glDeleteProgram(*program);
		delete program;
	});
	
}
