#include "Textureold.h"
#include "FreeImage.h"
#include <iostream>

Texture::Texture(const char * filename,const char* type)
	:mType(type),mFilename(filename)
{
	load(filename);
}

GLuint Texture::getTextureID()
{
	return mTexture;
}

void Texture::use(int id)
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

std::string Texture::getName()
{
	return mFilename;
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTexture);
}


//TODO: wczytywanie gdzies indziej
bool Texture::load(const char* filename)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error before creating texture " << filename << " " << glewGetErrorString(error) << std::endl;
		//return false;
	}
	//FreeImage_Initialise();
	

	FIBITMAP * data = FreeImage_Load(FreeImage_GetFIFFromFilename(filename), filename);
	FIBITMAP * bitmap = FreeImage_ConvertTo32Bits(data);
	mWidth = FreeImage_GetWidth(bitmap);
	mHeight = FreeImage_GetHeight(bitmap);

	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	//GL_LINEAR_MIPMAP_NEAREST : takes the nearest mipmap level and samples using linear interpolation.
	//GL_NEAREST_MIPMAP_LINEAR : linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation.
	//GL_LINEAR_MIPMAP_LINEAR : linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR); GL_TEXTURE_WRAP_S,GL_TEXTURE_WRAP_T, if 3d GL_TEXTURE_WRAP_R
	//GL_REPEAT: The default behavior for textures.Repeats the texture image.
	//GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
	//GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
	//GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.

	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));
	glGenerateMipmap(GL_TEXTURE_2D);
//	GLenum 
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error creating texture " << filename <<" "<< glewGetErrorString(error)<< std::endl;
		//return false;
	}


	FreeImage_Unload(bitmap);
	FreeImage_Unload(data);

	glBindTexture(GL_TEXTURE_2D, 0);


	return true;


	//uzywane tylko wtedy gdy linkujemy freeimage statycznie, na innych systemach prawdopodobnie zawsze trzeba uzyc
	//FreeImage_Initialise();
	//FreeImage_DeInitialise();
}