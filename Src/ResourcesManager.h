#include <map>

#include "Framework.h"

#define CacheImageName(imgN, w, h) ResourcesManager::getInstance()->cacheImage(imgN, w, h);

class ResourcesManager
{
public:
	ResourcesManager();
	~ResourcesManager();

	static ResourcesManager * getInstance();
	static void DestroyInstance();

	Texture *cacheImage(const char *imgName, int &w, int &h);
private:
	static ResourcesManager * ms_Instance;

	std::map<const char *, Texture*> *m_textureCacher;
};
