#include "Texture.h"
#include <iostream>

using namespace cote::graphic;


Texture::Texture(size_t width, size_t height)
{
	glGenTextures(1, &m_handler);
}

GLuint Texture::getTextureID()
{
	return m_handler;
}

void Texture::bind(unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	bindImpl();
}

void cote::graphic::Texture::unbind(unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	unbindImpl();
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handler);
}

cote::graphic::Texture2d::Texture2d(size_t width, size_t height, const uint8_t * data):Texture(width,height)
{
	glBindTexture(GL_TEXTURE_2D, m_handler);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	//GL_LINEAR_MIPMAP_NEAREST : takes the nearest mipmap level and samples using linear interpolation.
	//GL_NEAREST_MIPMAP_LINEAR : linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation.
	//GL_LINEAR_MIPMAP_LINEAR : linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.


	//GL_REPEAT: The default behavior for textures.Repeats the texture image.
	//GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
	//GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
	//GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data);
	glGenerateMipmap(GL_TEXTURE_2D);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error creating texture " << " " << glewGetErrorString(error) << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void cote::graphic::Texture2d::bindImpl()
{
	glBindTexture(GL_TEXTURE_2D, m_handler);
}

void cote::graphic::Texture2d::unbindImpl()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}