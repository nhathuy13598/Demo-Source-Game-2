#pragma once
#include "GameScreen.h"

#include "TextDisplay.h"

class HelpScreen : public GameScreen
{
public:
	HelpScreen();
	~HelpScreen();

	void OnKeyDown(int key);

	void update(float dt);

	void render();

private:
	GGameSprite * m_background, *m_guildeTexture;
	TextDisplay *m_Title;
};