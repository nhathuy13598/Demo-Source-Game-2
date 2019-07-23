#include "TextDisplay.h"

TextDisplay::~TextDisplay()
{
	fwDestroyTexture(m_texture);
}

TextDisplay::TextDisplay(const char *text, TTF_Font *font, int fontSize) {
	m_font = font;
	m_currentText = text;
	m_fontSize = fontSize;

	fwLoadTextFont(text, font, m_texture, m_rect.w, m_rect.h);
	float ratio = (float)fontSize / m_rect.h;
	m_rect.h = fontSize;
	m_rect.w *= ratio;
	m_scale = 1;
	m_angle = 0;
}

void TextDisplay::setText(const char * text)
{
	if (SDL_strcmp(m_currentText, text) != 0) {
		fwDestroyTexture(m_texture);
		fwLoadTextFont(text, m_font, m_texture, m_rect.w, m_rect.h);

		float ratio = (float)m_fontSize / m_rect.h;
		m_rect.h = m_fontSize;
		m_rect.w *= ratio;
		m_scale = 1;
	}
}