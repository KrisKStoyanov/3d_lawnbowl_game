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

class Lightmap
{
public:
	Lightmap(std::string difImageAddress, std::string specImageAddress, bool repeatWrap);
	~Lightmap();
	BitMapFile* diffuseImage;
	BitMapFile* specularImage;
	GLuint diffuseIndex, specularIndex;
};

