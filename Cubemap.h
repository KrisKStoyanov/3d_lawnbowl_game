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

#include <vector>

class Cubemap
{
public:
	Cubemap(std::string _right, std::string _left, std::string _top, std::string _bottom, std::string _back, std::string _front);
	~Cubemap();

	BitMapFile* right;
	BitMapFile* left;
	BitMapFile* top;
	BitMapFile* bottom;
	BitMapFile* back;
	BitMapFile* front;

	GLuint textureId;
};

