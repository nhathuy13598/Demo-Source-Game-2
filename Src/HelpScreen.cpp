#include "HelpScreen.h"
#include "SharedVariables.h"
#include "GameScreenManager.h"
#include "GameConfigInfo.h"

HelpScreen::HelpScreen()
{
	m_background = new GGameSprite(HELP_BG);
	m_background->centerX(0, DEF_WIDTH);
	m_background->centerY(0, DEF_HEIGHT);


	m_guildeTexture = new GGameSprite("Guilde.png");
	m_guildeTexture->centerX(0, DEF_WIDTH);
	m_guildeTexture->centerY(0, DEF_HEIGHT);
	
	m_Title = new TextDisplay(HELP_TITLE, g_font, 100);
	m_Title->centerX(0, DEF_WIDTH);
	m_Title->setY(10);
}

HelpScreen::~HelpScreen()
{
	delete m_background;
	delete m_guildeTexture;
	delete m_Title;
}

void HelpScreen::OnKeyDown(int key) {
	// skip
	GameScreenManager::getInstance()->showMainMenuScreen();
}

void HelpScreen::update(float dt) {

}

void HelpScreen::render() {
	m_background->render();
	m_guildeTexture->render();
	m_Title->render();
}