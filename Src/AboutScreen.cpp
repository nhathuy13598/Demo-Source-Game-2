#include "AboutScreen.h"

#include "GameScreenManager.h"

#include "SharedVariables.h"
#include "GameConfigInfo.h"

AboutScreen::AboutScreen()
{
	m_background = new GGameSprite(ABOUT_BG);
	m_background->centerX(0, DEF_WIDTH);
	m_background->centerY(0, DEF_HEIGHT);
	
	m_title = new TextDisplay(ABOUT_TITLE, g_font, 100);
	m_title->centerX(0, DEF_WIDTH);

	int textMaggin = 40;
	int textH = m_title->getRect().h + textMaggin;

	m_name = new TextDisplay(DEVELOPER_NAME, g_font, 80);
	m_name->centerX(0, DEF_WIDTH);

	 textH += m_name->getRect().h + textMaggin;

	m_desc = new TextDisplay(ABOUT_DESC, g_font, 100);
	m_desc->centerX(0, DEF_WIDTH);

	 textH += m_desc->getRect().h;
	int textY = (DEF_HEIGHT - textH) / 2;

	m_title->setY(textY);
	textY += m_title->getRect().h + textMaggin;
	m_name->setY(textY);
	textY += m_name->getRect().h + textMaggin;
	m_desc->setY(textY);

}

AboutScreen::~AboutScreen()
{

	delete m_background;
	delete m_title;
	delete m_name;
	delete m_desc;
}

void AboutScreen::OnKeyDown(int key) {
	// skip
	GameScreenManager::getInstance()->showMainMenuScreen();
}

void AboutScreen::update(float dt) {

}

void AboutScreen::render() {
	m_background->render();
	m_title->render();
	m_name->render();
	m_desc->render();
}