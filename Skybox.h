#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "getbmp.h"
#include "Cubemap.h"
#include "vertex.h"
#include "Camera.h"
#include "CustomShader.h"
#include <vector>
class Skybox
{
public:
	Skybox(Cubemap* cubemap);
	~Skybox();

	GLuint vao, vbo, ibo;
	GLuint cubemapLoc;

	std::vector<Vertex> skyboxVertices;
	std::vector<GLuint> skyboxIndices;
	Cubemap* skyCubemap = nullptr;

	void Setup();
	void Draw(Camera* mainCamera, CustomShader* shader);
};

