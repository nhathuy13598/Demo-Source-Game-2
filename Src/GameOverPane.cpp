#include "GameOverPane.h"

#include "SharedVariables.h"
#include "GameConfigInfo.h"

GameOverPane::GameOverPane() : InGameMenu()
{
	m_Title = new TextDisplay(GAME_OVER_TITLE, g_font, 200);
	m_Title->centerX(0, DEF_WIDTH);

	int tH = m_Title->getRect().h + ITEM_SPACE;
	for (auto item : *m_items) {
		tH += item->getRect().h + ITEM_SPACE;
		if (item->getType() == InGameMenuItemType_CONTINUE) {
 			item->setText(REPLAY_TEXT);
			item->centerX(0, DEF_WIDTH);
			item->setIsSelecting(true);
		}
	}
	tH -= ITEM_SPACE;
	int tY = (DEF_HEIGHT - tH) / 2;

	m_Title->setY(tY);
	tY += m_Title->getRect().h + ITEM_SPACE;
	for (auto item : *m_items) {
		item->setY(tY);
		tY += item->getRect().h + ITEM_SPACE;
	}
}

GameOverPane::~GameOverPane()
{
	delete m_Title;
}

void GameOverPane::render()
{
	InGameMenu::render();
	m_Title->render();
}
