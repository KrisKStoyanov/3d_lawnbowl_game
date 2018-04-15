#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::UploadTexture(std::string textureKey, Texture * texture)
{
	textures[textureKey] = texture;
}

Texture * TextureManager::GetTexture(std::string textureKey)
{
	return textures[textureKey];
}

void TextureManager::UploadLightmap(std::string lightmapKey, Lightmap * lightmap)
{
	lightmaps[lightmapKey] = lightmap;
}

Lightmap * TextureManager::GetLightmap(std::string lightmapKey)
{
	return lightmaps[lightmapKey];
}

void TextureManager::CleanMemory()
{
	for (auto pair : textures) {
		delete pair.second;
	}

	for (auto pair : lightmaps) {
		delete pair.second;
	}
}
