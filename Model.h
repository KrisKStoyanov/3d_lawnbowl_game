#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "CustomShader.h"

class Model
{
private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> loadedTextures;

	void LoadModel(std::string path);
public:
	Model(GLchar*path);
	~Model();

	GLint TextureFromFile(const char *path, std::string directory);
	void LoadModel(GLchar* path);
	void Draw(CustomShader shader, glm::mat4 model);
	void ProcessNode();
	Mesh ProcessMesh();
};

