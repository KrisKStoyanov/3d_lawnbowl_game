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

class Mesh 
{
public:
	
	/*Simple mesh prefab - glDrawArrays*/
	Mesh(std::vector<Vertex> meshVertices);
	//Advanced mesh prefab - glDrawElements
	Mesh(std::vector<Vertex> meshVertices, std::vector<unsigned int> meshIndices);

	Mesh();
	~Mesh();

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	std::vector<Vertex> meshVertices;
	std::vector<unsigned int> meshIndices;

	bool drawElements;

	void UploadArrayData(std::vector<Vertex> meshVertices);
	void UploadElementsData(std::vector<Vertex> meshVertices, std::vector<GLuint> meshIndices);

	void DrawArrayMesh(glm::mat4 model);
	void DrawElementsMesh(glm::mat4 model);

	void ClearMemory();
};

