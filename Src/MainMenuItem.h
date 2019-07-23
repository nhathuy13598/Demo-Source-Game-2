#pragma once

#include "TextDisplay.h"

typedef enum MainMenuItemType {
	MainMenuItemType_Play,
	MainMenuItemType_Continue,
	MainMenuItemType_NewGame,
	MainMenuItemType_Help,
	MainMenuItemType_About
} MenuItemType;

class MainMenuItem  
{
public:
	MainMenuItem(const char *text, MainMenuItemType t);
	~MainMenuItem();

	void setCenterX(int x);
	void setCenterY(int y);

	void setX(int x);
	void setY(int y);

	Rect getRect();

	void update(float dt);
	void render();

	bool isSelected();
	void setSelecting(bool s);

	MainMenuItemType getType();
private:
	TextDisplay *m_sprite;
	MainMenuItemType m_Type;
	bool m_isSelected;
};