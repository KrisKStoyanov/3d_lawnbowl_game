#include "CameraManager.h"

CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

void CameraManager::UploadCamera(std::string cameraKey, Camera * cameraData)
{
	cameras[cameraKey] = cameraData;
}

Camera * CameraManager::GetCamera(std::string cameraKey)
{
	return cameras[cameraKey];
}

void CameraManager::CleanMemory()
{
	for (auto pair : cameras) {
		delete pair.second;
	}
}
