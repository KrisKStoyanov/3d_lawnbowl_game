#pragma once
#include "Camera.h"
#include <map>

class CameraManager
{
private:
	std::map<std::string, Camera*> cameras;
public:
	CameraManager();
	~CameraManager();
	void UploadCamera(std::string cameraKey, Camera* cameraData);
	Camera* GetCamera(std::string cameraKey);
	void CleanMemory();
};

