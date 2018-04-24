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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> loadedTextures;

public:
	Model(std::string path);
	~Model();

	Texture TextureFromFile(const GLchar *path, std::string directory);
	void LoadModel(std::string& path);
	void Draw(glm::mat4 model);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

	//Save material data for game object instanciating
	Material* modelMatColData;
};

