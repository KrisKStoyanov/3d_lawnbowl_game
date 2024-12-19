#pragma once
#include "CustomShader.h"
#include <map>

class ShaderManager
{
private:
	std::map<std::string, CustomShader*> shaders;
public:
	ShaderManager();
	~ShaderManager();
	void UploadShader(std::string shaderKey, CustomShader* shaderData);
	CustomShader* GetShader(std::string shaderKey);
	void CleanMemory();
};

