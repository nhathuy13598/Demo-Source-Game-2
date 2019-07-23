#pragma once
#include "ResourcesManager.h"

#include "SharedVariables.h"

ResourcesManager::~ResourcesManager() {
	for (auto pair : *m_textureCacher) {
		fwDestroyTexture(pair.second);
	}
	delete m_textureCacher;
}

ResourcesManager::ResourcesManager() {
	m_textureCacher = new std::map<const char *, Texture*>;
}

ResourcesManager * ResourcesManager::ms_Instance = 0;
ResourcesManager *ResourcesManager::getInstance() {
	if (!ms_Instance) {
		ms_Instance = new ResourcesManager();
	}
	return ms_Instance;
}

void ResourcesManager::DestroyInstance() {

}

Texture *ResourcesManager::cacheImage(const char * imgName, int &w, int &h)
{
	Texture *texture = nullptr;
	if (m_textureCacher->size()) {
		for (auto pair : *m_textureCacher) {
			if (strcmp(pair.first, imgName) == 0) {
				texture = m_textureCacher->at(imgName);
				SDL_QueryTexture(texture, NULL, NULL, &w, &h);
				break;
			}
		}
	}
	if (!texture) {
		auto texturePath = new std::string(SharedVariables::getInstance()->getTexturePath()->c_str());
		texturePath->append(imgName);
		fwLoadTexture(texturePath->c_str(), texture, w, h);
		if (texture) {
			std::pair<const char *, Texture*> pair (imgName, texture);
			m_textureCacher->insert(pair);
		}
		delete texturePath;
	}
	return texture;
}
