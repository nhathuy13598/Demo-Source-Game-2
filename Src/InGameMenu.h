#pragma once

#include "InGameMenuItem.h"

#include <vector>


#define ITEM_SPACE 50

class InGameMenuDelegate {
public:
	virtual void ingameMenuDidConfirm(InGameMenuItemType type) {};
};

class InGameMenu
{
public:
	InGameMenu();
	~InGameMenu();

	void OnKeyDown(int key);

	void update(float dt);
	void render();

	void setDelegate(InGameMenuDelegate * d);
protected:
	InGameMenuDelegate *m_delegate;
	Rect m_rect;
	SDL_Color m_coverColor;
	std::vector<InGameMenuItem*> *m_items;
	int m_selectingIndex;
};