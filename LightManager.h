#pragma once
#include "Light.h"
#include "DirLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <map>

class LightManager
{
private:
	std::map<std::string, Light*> lights;
	std::map<std::string, DirLight*> dirLights;
	std::map<std::string, PointLight*> pointLights;
	std::map<std::string, SpotLight*> spotLights;
public:
	LightManager();
	~LightManager();

	//Upload a light prefab to lights
	void UploadLight(std::string lightKey, Light* lightData);
	void UploadLight(std::string lightKey, DirLight* lightData);
	void UploadLight(std::string lightKey, PointLight* lightData);
	void UploadLight(std::string lightKey, SpotLight* lightData);

	Light* GetLight(std::string lightKey);
	DirLight* GetDirLight(std::string lightKey);
	PointLight* GetPointLight(std::string lightKey);
	SpotLight* GetSpotLight(std::string lightKey);

	void CleanMemory();
};

