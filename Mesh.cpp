#include "Mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> _meshVertices)
{
	meshVertices = _meshVertices;
	UploadArrayData(meshVertices);
}

Mesh::Mesh(std::vector<Vertex> _meshVertices, std::vector<unsigned int> _meshIndices)
{
	meshVertices = _meshVertices;
	meshIndices = _meshIndices;
	UploadElementsData(meshVertices, meshIndices);
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::UploadArrayData(std::vector<Vertex> _meshVertices)
{
	meshVertices = _meshVertices;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshVertices.size(), meshVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), (GLvoid*)sizeof(meshVertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), (GLvoid*)(sizeof(meshVertices[0].coords) + sizeof(meshVertices[0].color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), (GLvoid*)(sizeof(meshVertices[0].coords) + sizeof(meshVertices[0].color) + sizeof(meshVertices[0].uv)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	drawElements = false;
}

void Mesh::UploadElementsData(std::vector<Vertex> _meshVertices, std::vector<unsigned int> _meshIndices)
{
	meshVertices = _meshVertices;
	meshIndices = _meshIndices;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshVertices.size(), meshVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * meshIndices.size(), meshIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), (GLvoid*)sizeof(meshVertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), (GLvoid*)(sizeof(meshVertices[0].coords) + sizeof(meshVertices[0].color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(meshVertices[0]), (GLvoid*)(sizeof(meshVertices[0].coords) + sizeof(meshVertices[0].color) + sizeof(meshVertices[0].uv)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	drawElements = true;
}

void Mesh::DrawArrayMesh(glm::mat4 model)
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, meshVertices.size());
	glBindVertexArray(0);
}

void Mesh::DrawElementsMesh(glm::mat4 model)
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_STRIP, meshIndices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::ClearMemory()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

