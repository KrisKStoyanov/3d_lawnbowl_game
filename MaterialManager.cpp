#include "MaterialManager.h"

MaterialManager::MaterialManager()
{
}


MaterialManager::~MaterialManager()
{
}

void MaterialManager::UploadMaterial(std::string matKey, Material * material)
{
	materials[matKey] = material;
}

Material* MaterialManager::GetMaterial(std::string matKey)
{
	return materials[matKey];
}

void MaterialManager::CleanMemory()
{
	for (auto pair : materials) {
		delete pair.second;
	}
}
