#pragma once
#include "TextDisplay.h"

class EndStagePane
{
public:
	EndStagePane(int stg);
	~EndStagePane();
	
	void update(float dt);
	void render();

	void setNextStage(int stg);
private:
	TextDisplay *m_titleText;
	TextDisplay *m_descText;

	Rect m_rect;
	SDL_Color m_coverColor;
};