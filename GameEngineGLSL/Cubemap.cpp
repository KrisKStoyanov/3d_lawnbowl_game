#include "Cubemap.h"

Cubemap::Cubemap(std::string _right, std::string _left, std::string _top, std::string _bottom, std::string _back, std::string _front)
{
	right = getbmp(_right);
	left = getbmp(_left);
	top = getbmp(_top);
	bottom = getbmp(_bottom);
	back = getbmp(_back);
	front = getbmp(_front);

	glGenTextures(1, &textureId);


	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, right->sizeX, right->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, right->data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, left->sizeX, left->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, left->data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8, top->sizeX, top->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, top->data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8, bottom->sizeX, bottom->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, bottom->data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8, back->sizeX, back->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, back->data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8, front->sizeX, front->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, front->data);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 1000);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


Cubemap::~Cubemap()
{
}
