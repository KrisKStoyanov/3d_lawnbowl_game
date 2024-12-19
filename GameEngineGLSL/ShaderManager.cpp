#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::UploadShader(std::string shaderKey, CustomShader * shaderData)
{
	shaders[shaderKey] = shaderData;
}

CustomShader * ShaderManager::GetShader(std::string shaderKey)
{
	return shaders[shaderKey];
}

void ShaderManager::CleanMemory()
{
	for (auto pair : shaders) {
		delete pair.second;
	}
}
