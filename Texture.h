#pragma once
#include "getbmp.h"

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif

class Texture
{
public:
	Texture(std::string imageAddress, bool repeatWrap,int width = 0, int height = 0);
	Texture();
	~Texture();
	BitMapFile* image;
	GLuint textureIndex;
};

