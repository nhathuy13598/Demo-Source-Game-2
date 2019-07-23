#include "LogoScreen.h"

#include "GameScreenManager.h"

#include "GameDefines.h"
#include "ResourcesManager.h"
#include "GameConfigInfo.h"

LogoScreen::~LogoScreen()
{
	delete background;
}

LogoScreen::LogoScreen()
{
	background = new GGameSprite("logo.png");
	background->centerX(0, DEF_WIDTH);
	background->centerY(0, DEF_HEIGHT);

	showTime = 3.0;
	showTimeEnd = false;
}

void LogoScreen::OnKeyDown(int key) {
	showTime = 0; // skip
}

void LogoScreen::update(float dt) {
	showTime -= dt;
	background->setScale(background->getScale() + 0.001);
	if (showTime <= 0 && !showTimeEnd) {
		showTimeEnd = true;
		GameScreenManager::getInstance()->showMainMenuScreen();
	}
}

void LogoScreen::render() {
	background->render();
}