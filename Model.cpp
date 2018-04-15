#include "Model.h"

void Model::LoadModel(std::string path)
{

}

Model::Model(GLchar*path)
{
	LoadModel(path);
}


Model::~Model()
{
}

GLint Model::TextureFromFile(const char * path, std::string directory)
{
	std::string filename = std::string(path);
	filename = directory + "/" + filename;
	GLuint textureId;
	glGenTextures(1, &textureId);

	return textureId;
}

void Model::LoadModel(GLchar * path)
{
}

void Model::Draw(CustomShader shader, glm::mat4 model)
{
	for (GLuint i = 0; i < meshes.size(); i++) {
		meshes[i].DrawElementsMesh(model);
	}
}
