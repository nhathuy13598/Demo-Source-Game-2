#include "InGameMenu.h"
#include "GameDefines.h"
#include "GameConfigInfo.h"

InGameMenu::InGameMenu()
{
	m_items = new std::vector<InGameMenuItem*>;
	
	int itemH = 0;
	auto continueItem = new InGameMenuItem(CONTINUE_TEXT, InGameMenuItemType_CONTINUE);
	m_items->push_back(continueItem);
	itemH += continueItem->getRect().h;

	auto quitItem = new InGameMenuItem(QUIT_TEXT, InGameMenuItemType_QUIT);
	m_items->push_back(quitItem);
	itemH += quitItem->getRect().h + ITEM_SPACE;

	int itemY = (DEF_HEIGHT - itemH) / 2;
	for (auto item : *m_items) {
		item->centerX(0, DEF_WIDTH);
		item->setY(itemY);
		itemY += item->getRect().h + ITEM_SPACE;
	}
	continueItem->setIsSelecting(true);
	m_selectingIndex = 0;

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = DEF_WIDTH;
	m_rect.h = DEF_HEIGHT;

	m_coverColor.r = 0;
	m_coverColor.g = 0;
	m_coverColor.b = 0;
	m_coverColor.a = 180;
}

InGameMenu::~InGameMenu()
{
	for (auto item : *m_items) {
		delete item;
	}
	delete m_items;
}

void InGameMenu::OnKeyDown(int key)
{
	switch (key)
	{
	case SDLK_w:
	case SDLK_UP:
		m_selectingIndex--;
		if (m_selectingIndex < 0) {
			m_selectingIndex = m_items->size() - 1;
		}
		for (int i = 0; i < m_items->size(); i++) {
			m_items->at(i)->setIsSelecting(i == m_selectingIndex);
		}
		break;
	case SDLK_s:
	case SDLK_DOWN:
		m_selectingIndex++;
		if (m_selectingIndex >= m_items->size()) {
			m_selectingIndex = 0;
		}
		for (int i = 0; i < m_items->size(); i++) {
			m_items->at(i)->setIsSelecting(i == m_selectingIndex);
		}
		break;
	case SDLK_RETURN:
	case SDLK_SPACE: {
		auto selectingType = m_items->at(m_selectingIndex)->getType();
		if (m_delegate) {
			m_delegate->ingameMenuDidConfirm(selectingType);
		}
	}
		break;
	default:
		break;
	}
}

void InGameMenu::update(float dt)
{
}

void InGameMenu::render()
{
	fwFillRect(m_rect, m_coverColor);
	for (auto item : *m_items) {
		item->render();
	}
}

void InGameMenu::setDelegate(InGameMenuDelegate * d)
{
	m_delegate = d;
}
