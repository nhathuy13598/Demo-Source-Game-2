#include "GameScreenManager.h"

#include "LogoScreen.h"
#include "MainMenuScreen.h"
#include "AboutScreen.h"
#include "HelpScreen.h"
#include "GameplayScreen.h"
#include "SharedVariables.h"

static GameScreen * currentScreen = nullptr;

GameScreenManager::GameScreenManager()
{
	m_gameScreens = new std::vector<GameScreen*>();
}

GameScreenManager::~GameScreenManager()
{
}

GameScreen * GameScreenManager::getCurrentScreen() {
	return currentScreen;
}
GameScreenManager * GameScreenManager::ms_Instance = 0;
GameScreenManager * GameScreenManager::getInstance()
{ 
	if (!ms_Instance) {
		ms_Instance = new GameScreenManager();
	}  
	return ms_Instance; 
}

void GameScreenManager::DestroyInstance() {
	if (ms_Instance) {
		delete ms_Instance;
		ms_Instance = 0;
	} 
}

void GameScreenManager::update(float dt)
{
	SHARE_CalcCurrentFPS(dt);
	if (currentScreen) {
		currentScreen->update(dt);
	}
}

void GameScreenManager::render()
{
	if (currentScreen) {
		currentScreen->render();
	}
}

void GameScreenManager::OnKeyDown(int key)
{
	if (currentScreen) {
		currentScreen->OnKeyDown(key);
	}
}

void GameScreenManager::OnKeyUp(int key)
{
	if (currentScreen) {
		currentScreen->OnKeyUp(key);
	}
}

void GameScreenManager::showLogoScreen() {
	if (!currentScreen) {
		LogoScreen * screen = new LogoScreen();
		showScreen(screen);
	}
}

void GameScreenManager::showMainMenuScreen() {
	MainMenuScreen * screen = new MainMenuScreen();
	return showScreen(screen);
}

void GameScreenManager::showAboutScreen() {
	AboutScreen * screen = new AboutScreen();
	return showScreen(screen);
}

void GameScreenManager::showHelpScreen() {
	HelpScreen * screen = new HelpScreen();
	return showScreen(screen);
}

void GameScreenManager::showInGameScreen() {
	GameplayScreen * screen = new GameplayScreen();
	return showScreen(screen);
}


void GameScreenManager::showScreen(GameScreen * screen) {
	if (screen) {
		if (currentScreen) {
			currentScreen->screenWillHide();
			delete currentScreen;
		}
		currentScreen = screen;
		currentScreen->screenDidShow();
	} 
}

void GameScreenManager::terminate() {
	for (auto screen : *m_gameScreens) {
		delete screen;
	}
	delete m_gameScreens;

	currentScreen = nullptr;
}