#include "ModelManager.h"



ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

void ModelManager::UploadModel(std::string key, Model * modelData)
{
	models[key] = modelData;
}

Model* ModelManager::GetModel(std::string key)
{
	return models[key];
}

void ModelManager::CleanMemory()
{
	for (auto pair : models) {
		delete pair.second;
	}
}
