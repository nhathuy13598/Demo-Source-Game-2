#pragma once

#include "GameScreen.h"

#include "GGameSprite.h"

class LogoScreen : public GameScreen
{
private:
	GGameSprite *background;

	float showTime;
	bool showTimeEnd;
public:
	LogoScreen();
	~LogoScreen();

	void OnKeyDown(int key);
	void update(float dt);
	void render();

};