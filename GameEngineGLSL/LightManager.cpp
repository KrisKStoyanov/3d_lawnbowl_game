#include "LightManager.h"

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

void LightManager::UploadLight(std::string lightKey, Light * lightData)
{
	lights[lightKey] = lightData;
}

void LightManager::UploadLight(std::string lightKey, DirLight * lightData)
{
	dirLights[lightKey] = lightData;
}

void LightManager::UploadLight(std::string lightKey, PointLight * lightData)
{
	pointLights[lightKey] = lightData;
}

void LightManager::UploadLight(std::string lightKey, SpotLight * lightData)
{
	spotLights[lightKey] = lightData;
}

Light * LightManager::GetLight(std::string lightKey)
{
	return lights[lightKey];
}

DirLight * LightManager::GetDirLight(std::string lightKey)
{
	return dirLights[lightKey];
}

PointLight * LightManager::GetPointLight(std::string lightKey)
{
	return pointLights[lightKey];
}

SpotLight * LightManager::GetSpotLight(std::string lightKey)
{
	return spotLights[lightKey];
}

void LightManager::CleanMemory()
{
	for (auto pair : lights) {
		delete pair.second;
	}
}
