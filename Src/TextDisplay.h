#pragma once
#include "GGameSprite.h"

class TextDisplay : public GGameSprite
{
public:
	~TextDisplay();

	TextDisplay(const char *text, TTF_Font *font, int fontSize = 20);

	void setText(const char *text);
private:
	const char *m_currentText;
	TTF_Font *m_font; // weak pointer
	int m_fontSize;
};