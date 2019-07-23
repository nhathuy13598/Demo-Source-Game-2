#include "MainMenuScreen.h"

#include "GameScreenManager.h"
#include "SharedVariables.h"
#include "GameConfigInfo.h"
#include "GameDefines.h"

MainMenuScreen::MainMenuScreen()
{
	m_background = new GGameSprite(MAIN_MENU_BG);
	m_background->centerY(0, DEF_HEIGHT);
	m_background->centerX(0, DEF_WIDTH);

	m_logoNames = new std::vector<std::string*>;
	m_logoNames->push_back(new std::string(LOGO_GAME_1));
	m_logoNames->push_back(new std::string(LOGO_GAME_2));
	m_logoNames->push_back(new std::string(LOGO_GAME_3));


	m_logoIndex = 0;
	m_logo = new GGameSprite(m_logoNames->at(m_logoIndex)->c_str());
	m_logoDelay = 0.3;
	m_logo->centerX(0, DEF_WIDTH);

	m_items = new std::vector<MainMenuItem*>();
	
	int itemH = m_logo->getRect().h;
	
	int stage = 1;
	int plv = 1;
	int sc = 0;
	SharedVariables::getInstance()->loadGame(stage, plv, sc);
	std::string *playTitle = new std::string(PLAY_TITLE);
	if (stage > 1) {
		playTitle->assign(CONTINUE_TEXT);
	}
	MainMenuItem *playItem = new MainMenuItem(playTitle->c_str(), MainMenuItemType_Play);
	m_items->push_back(playItem);
	itemH += playItem->getRect().h;
	playItem->setSelecting(true);

	MainMenuItem *helpItem = new MainMenuItem(HELP_TITLE, MainMenuItemType_Help);
	m_items->push_back(helpItem);
	itemH += helpItem->getRect().h;

	MainMenuItem *aboutItem = new MainMenuItem(ABOUT_TITLE, MainMenuItemType_About);
	m_items->push_back(aboutItem);
	itemH += aboutItem->getRect().h;


	int itemMaggin = 40;
	itemH += itemMaggin * m_items->size(); 
	int itemY = (DEF_HEIGHT - itemH) / 2;
	// layout
	m_logo->setY(itemY);
	itemY += (m_logo->getRect().h + itemMaggin);

	for (auto item : *m_items) {
		item->setCenterX(DEF_WIDTH / 2);
		item->setY(itemY);
		itemY += (item->getRect().h + itemMaggin);
	}


	m_itemPointer = new GGameSprite("Pointer.png");
	m_itemPointer->centerY(playItem->getRect().y, playItem->getRect().h);
	m_itemPointer->setX(playItem->getRect().x - m_itemPointer->getRect().w - playItem->getRect().w / 2);
}

MainMenuScreen::~MainMenuScreen()
{
	delete m_background;
	for (int i = 0; i < m_items->size(); i++) {
		MainMenuItem * item = m_items->at(i);
		delete item;
	}
	delete m_items;

	for (auto str : *m_logoNames) {
		delete str;
	}
	delete m_logoNames;

	delete m_logo;

	delete m_itemPointer;
}

void MainMenuScreen::OnKeyDown(int key) {
	
	switch (key)
	{
	case SDLK_w:
	case SDLK_UP:
		m_selectingIndex--;
		if (m_selectingIndex < 0) {
			m_selectingIndex = m_items->size() - 1;
		}
		for (int i = 0; i < m_items->size(); i++) {
			auto item = m_items->at(i);
			item->setSelecting(i == m_selectingIndex);
			if (item->isSelected()) {
				m_itemPointer->centerY(item->getRect().y, item->getRect().h);
				m_itemPointer->setX(item->getRect().x - m_itemPointer->getRect().w - item->getRect().w / 2);
			}
		}
		break;
	case SDLK_s:
	case SDLK_DOWN:
		m_selectingIndex++;
		if (m_selectingIndex >= m_items->size()) {
			m_selectingIndex = 0;
		}
		for (int i = 0; i < m_items->size(); i++) {
			auto item = m_items->at(i);
			item->setSelecting(i == m_selectingIndex);
			if (item->isSelected()) {
				m_itemPointer->centerY(item->getRect().y, item->getRect().h);
				m_itemPointer->setX(item->getRect().x - m_itemPointer->getRect().w - item->getRect().w / 2);
			}
		}
		break;
	case SDLK_RETURN:
	case SDLK_SPACE: {
		auto selectingType = m_items->at(m_selectingIndex)->getType();
		switch (selectingType)
		{
		case MainMenuItemType_Play:
			GameScreenManager::getInstance()->showInGameScreen();
			break;
		case MainMenuItemType_Continue:
			break;
		case MainMenuItemType_NewGame:
			break;
		case MainMenuItemType_Help:
			GameScreenManager::getInstance()->showHelpScreen();
			break;
		case MainMenuItemType_About:
			GameScreenManager::getInstance()->showAboutScreen();
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}

void MainMenuScreen::update(float dt) {
	m_logoDelay -= dt;
	if (m_logoDelay <= 0) {
		m_logoDelay = 0.3;
		m_logoIndex++;
		if (m_logoIndex >= m_logoNames->size()) {
			m_logoIndex = 0;
		}
		m_logo->setTexture(m_logoNames->at(m_logoIndex)->c_str());
	}
}

void MainMenuScreen::render() {
	m_background->render();
	m_logo->render();
	for (auto item : *m_items) {
		item->render();
	}
	m_itemPointer->render();
}