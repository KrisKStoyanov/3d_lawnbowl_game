#ifndef GETBMP_H
#define GETBMP_H

#include <fstream>
#include <string>

struct BitMapFile
{
	int sizeX;
	int sizeY;
	char *data;
};

BitMapFile *getbmp(std::string filename);

#endif