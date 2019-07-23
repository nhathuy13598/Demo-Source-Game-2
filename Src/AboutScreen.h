#pragma once
#include "GameScreen.h"
#include "TextDisplay.h"

class AboutScreen : public GameScreen
{
public:
	AboutScreen();
	~AboutScreen();

	void OnKeyDown(int key);

	void update(float dt);

	void render();

private:
	GGameSprite * m_background;
	TextDisplay *m_title, *m_name, *m_desc;
};