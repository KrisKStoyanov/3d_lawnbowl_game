#include "MeshManager.h"
#include <iostream>

MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
}

void MeshManager::UploadMesh(std::string meshKey, Mesh * meshData)
{
	meshes[meshKey] = meshData;
	//meshes.insert(std::pair<std::string, Mesh*>(meshKey, meshData));
}

void MeshManager::UploadSphereMesh(std::string meshKey, int slices, int stacks, int radius)
{
	std::vector<Vertex> sVerts;
	std::vector<GLuint> sIndices;

	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;
			GLfloat theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			//meshVertices.push_back((glm::vec4(x * radius, y * radius + 6.0, z * radius, 1.0), glm::vec4(1.0,1.0,1.0,1.0), glm::vec2(0.0,0.0), glm::vec3(x, y, z);
			Vertex vert;
			vert.coords = glm::vec4(x * radius, y * radius, z * radius, 1.0);
			vert.normal = glm::vec3(x, y, z); 
			float piVal = 3.14159;
			vert.uv = glm::vec2((glm::asin(vert.normal.x) / piVal + 0.5f), (glm::asin(vert.normal.y) / piVal  + 0.5f));
			vert.color = glm::vec4(1.0, 1.0, 1.0, 1.0);

			sVerts.push_back(vert);

			//count++;
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		sIndices.push_back(i);
		sIndices.push_back(i + slices + 1);
		sIndices.push_back(i + slices);

		sIndices.push_back(i + slices + 1);
		sIndices.push_back(i);
		sIndices.push_back(i + 1);
	}

	Mesh* sphere = new Mesh(sVerts, sIndices);
	meshes[meshKey] = sphere;
}

void MeshManager::UploadCubeMesh(std::string meshKey, float width, float height, float depth)
{
	std::vector<Vertex> cVerts (8);
	std::vector<GLuint> cIndices;

	cVerts[0].coords = glm::vec4(-width, -height, -depth, 1.0f); //0
	cVerts[1].coords = glm::vec4(width, -height, -depth, 1.0f); //1
	cVerts[2].coords = glm::vec4(width, height, -depth, 1.0f); //2
	cVerts[3].coords = glm::vec4(-width, height, -depth, 1.0f); //3
	cVerts[4].coords = glm::vec4(-width, -height, depth, 1.0f); //4
	cVerts[5].coords = glm::vec4(width, -height, depth, 1.0f); //5
	cVerts[6].coords = glm::vec4(width, height, depth, 1.0f); //6
	cVerts[7].coords = glm::vec4(-width, height, depth, 1.0f); //7

	cVerts[0].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[1].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[2].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[3].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[4].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[5].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[6].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
	cVerts[7].color = glm::vec4(1.0, 1.0, 1.0, 1.0f);

	cVerts[0].uv = glm::vec2(0.0, 0.0);
	cVerts[1].uv = glm::vec2(1.0, 0.0);
	cVerts[2].uv = glm::vec2(1.0, 1.0);
	cVerts[3].uv = glm::vec2(0.0, 1.0);
	cVerts[4].uv = glm::vec2(0.0, 0.0);
	cVerts[5].uv = glm::vec2(1.0, 0.0);
	cVerts[6].uv = glm::vec2(1.0, 1.0);
	cVerts[7].uv = glm::vec2(0.0, 1.0);

	cVerts[0].normal = glm::vec3(0.0, 0.0, -1.0);
	cVerts[1].normal = glm::vec3(0.0, 0.0, -1.0);
	cVerts[2].normal = glm::vec3(0.0, 0.0, -1.0);
	cVerts[3].normal = glm::vec3(0.0, 0.0, -1.0);
	cVerts[4].normal = glm::vec3(0.0, 0.0, 1.0);
	cVerts[5].normal = glm::vec3(0.0, 0.0, 1.0);
	cVerts[6].normal = glm::vec3(0.0, 0.0, 1.0);
	cVerts[7].normal = glm::vec3(0.0, 0.0, 1.0);

	cIndices.push_back(0);
	cIndices.push_back(2);
	cIndices.push_back(1);
	cIndices.push_back(0);
	cIndices.push_back(3);
	cIndices.push_back(2);

	cIndices.push_back(1);
	cIndices.push_back(2);
	cIndices.push_back(6);
	cIndices.push_back(6);
	cIndices.push_back(5);
	cIndices.push_back(1);

	cIndices.push_back(4);
	cIndices.push_back(5);
	cIndices.push_back(6);
	cIndices.push_back(6);
	cIndices.push_back(7);
	cIndices.push_back(4);

	cIndices.push_back(2);
	cIndices.push_back(3);
	cIndices.push_back(6);
	cIndices.push_back(6);
	cIndices.push_back(7);
	cIndices.push_back(3);

	cIndices.push_back(0);
	cIndices.push_back(7);
	cIndices.push_back(3);
	cIndices.push_back(0);
	cIndices.push_back(4);
	cIndices.push_back(7);

	cIndices.push_back(0);
	cIndices.push_back(1);
	cIndices.push_back(5);
	cIndices.push_back(0);
	cIndices.push_back(5);
	cIndices.push_back(4);

	Mesh* cube = new Mesh(cVerts, cIndices);
	meshes[meshKey] = cube;
}

Mesh* MeshManager::GetMesh(std::string meshKey)
{
	return meshes[meshKey];
}


void MeshManager::CleanMemory()
{
	for (auto pair : meshes) {
		delete pair.second;
	}
}
