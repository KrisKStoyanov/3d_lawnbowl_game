#pragma once
#include "Model.h"
#include <map>

class ModelManager
{
private:
	std::map<std::string, Model*> models;
public:
	ModelManager();
	~ModelManager();

	void UploadModel(std::string key, Model* modelData);
	Model* GetModel(std::string key);

	void CleanMemory();
};

