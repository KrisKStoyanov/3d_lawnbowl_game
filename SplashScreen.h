#pragma once
#include "GameObject.h"
class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();
	void Setup(glm::vec3 cameraPosition, std::string imageAddress);
	void Draw(CustomShader* shader);
	bool active;
	GLuint vao, vbo, ibo;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	BitMapFile* image;
	GLuint textureIndex;
	GLuint textureLoc;
};

