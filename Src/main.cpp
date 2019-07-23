#include "Framework.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "GameScreenManager.h"
#include "SharedVariables.h"
#include "ResourcesManager.h"
#include "GameConfigInfo.h"

void update(float dt) {
	GameScreenManager::getInstance()->update(dt);
}

void render() {
	GameScreenManager::getInstance()->render();
}
void OnKeyDown(int key) {
	GameScreenManager::getInstance()->OnKeyDown(key);
}

void OnKeyUp(int key) {
	GameScreenManager::getInstance()->OnKeyUp(key);
}

int main(int argc, char *argv[])
{

	GameConfigInfo::getInstance()->loadConfig();

	fwInit(DEF_WIDTH, DEF_HEIGHT);
	fwSetFPS(DEF_FPS);
	
	fwRegisterUpdateCallback(update);
	fwRegisgerRenderCallback(render);
	fwRegisterOnKeyDownCallback(OnKeyDown);
	fwRegisterOnKeyUpCallback(OnKeyUp);

	GameScreenManager::getInstance()->showLogoScreen();
	SharedVariables::getInstance()->load();
	ResourcesManager::getInstance();

	fwLoop();
	
	fwTerminate();

	GameScreenManager::getInstance()->terminate();

	GameScreenManager::DestroyInstance();
	SharedVariables::DestroyInstance();
	ResourcesManager::DestroyInstance();
	GameConfigInfo::DestroyInstance();

	return 0;
}