#pragma once
#include "Material.h"
#include <map>

class MaterialManager
{
private:
	std::map<std::string, Material*> materials;
public:
	MaterialManager();
	~MaterialManager();

	void UploadMaterial(std::string matKey, Material* material);

	Material* GetMaterial(std::string matKey);

	void CleanMemory();
};

