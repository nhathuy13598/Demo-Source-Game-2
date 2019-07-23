#pragma once
#include "InGameMenu.h"
class GameOverPane : public InGameMenu
{
public:
	GameOverPane();
	~GameOverPane();
	void render();
private:
	TextDisplay *m_Title;
};
