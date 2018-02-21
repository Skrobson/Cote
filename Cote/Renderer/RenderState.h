#pragma once
#include <GL\glew.h>
enum CullFaceSite {
	BACK = GL_BACK,
	FRONT = GL_FRONT,
	FRON_AND_BACK = GL_FRONT_AND_BACK
};

class RenderState
{
public:
	RenderState();

	bool cullFace = true;
	bool depthTest = true;

	CullFaceSite cullSite = CullFaceSite::BACK;
};

