#pragma once
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif

#include "vertex.h"
#include <vector>

#include "Texture.h"

class Mesh 
{
public:
	
	//Simple mesh prefab - glDrawArrays
	Mesh(std::vector<Vertex> meshVertices);
	//Advanced mesh prefab - glDrawElements
	Mesh(std::vector<Vertex> meshVertices, std::vector<GLuint> meshIndices);
	//Mesh containing texture data
	Mesh(std::vector<Vertex> meshVertices, std::vector<GLuint> meshIndices, std::vector<Texture> meshTextures);

	Mesh();
	~Mesh();

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	std::vector<Vertex> meshVertices;
	std::vector<GLuint> meshIndices;
	std::vector<Texture> meshTextures;

	bool drawElements;

	void UploadArrayData(std::vector<Vertex> meshVertices);
	void UploadElementsData(std::vector<Vertex> meshVertices, std::vector<GLuint> meshIndices);
	void UploadElemTexData(std::vector<Vertex> meshVertices, std::vector<GLuint> meshIndices, std::vector<Texture> meshTextures);

	void DrawArrayMesh(glm::mat4 model);
	void DrawElementsMesh(glm::mat4 model);
	void DrawElemTriMesh(glm::mat4 model);

	void DrawElemTexMesh(glm::mat4 model);

	void ClearMemory();
};

