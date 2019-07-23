#pragma once

#include "GameScreen.h"

#include <vector>

class GameScreenManager
{
public:
	~GameScreenManager();

	static GameScreenManager * getInstance();
	static void DestroyInstance();

	void OnKeyDown(int key);
	void OnKeyUp(int key);

	void update(float dt);
	void render();

	void showLogoScreen();
	void showMainMenuScreen();
	void showAboutScreen();
	void showHelpScreen();
	void showInGameScreen();

	void terminate();

	GameScreen * getCurrentScreen();

protected:
	GameScreenManager();
private:
	static GameScreenManager * ms_Instance;
	void showScreen(GameScreen * screen);

	std::vector<GameScreen*> *m_gameScreens;
};