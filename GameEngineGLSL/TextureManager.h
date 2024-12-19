#pragma once
#include "Texture.h"
#include "Lightmap.h"
#include <map>

class TextureManager
{
private:
	std::map<std::string, Texture*> textures;
	std::map<std::string, Lightmap*> lightmaps;
public:
	TextureManager();
	~TextureManager();
	void UploadTexture(std::string textureKey, Texture* texture);
	Texture* GetTexture(std::string textureKey);
	void UploadLightmap(std::string lightmapKey, Lightmap* lightmap);
	Lightmap* GetLightmap(std::string lightmapKey);
	void CleanMemory();
};

