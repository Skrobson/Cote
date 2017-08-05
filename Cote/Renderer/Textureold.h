#pragma once
#include <GL/glew.h>
#include <string>
//TODO: initialize gdzies indziej, np do textureManagera
#define TEX_DIFFUSE "texture_diffuse"
#define TEX_SPECULAR "texture_specular"
#define TEX_NORMALS   "texture_normals"
class Texture
{
public:
	Texture(const char * filename, const char* type);

	GLuint getTextureID();

	void use(int id);
	std::string getName();
	~Texture();

private:
	int mWidth, mHeight;
	bool load(const char* filename);

	GLuint mTexture;
	std::string mType;
	std::string mFilename;
};

