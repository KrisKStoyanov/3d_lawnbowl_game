#pragma once
#include "Mesh.h"
#include <map>

class MeshManager
{
private:
	std::map<std::string, Mesh*> meshes;
public:
	MeshManager();
	~MeshManager();

	//Create undefined mesh
	void UploadMesh(std::string meshKey, Mesh* meshData);

	//Create sphere mesh
	void UploadSphereMesh(std::string meshKey, int slices, int stacks, int radius);

	//Create cube mesh
	void UploadCubeMesh(std::string meshKey, float width, float height, float depth);

	Mesh* GetMesh(std::string meshKey);
	void CleanMemory();
};

