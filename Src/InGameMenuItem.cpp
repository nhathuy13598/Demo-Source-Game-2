#include "InGameMenuItem.h"
#include "SharedVariables.h"

InGameMenuItem::InGameMenuItem(const char * text, InGameMenuItemType t) : TextDisplay(text, g_font, 100)
{
	m_type = t;
}

InGameMenuItem::~InGameMenuItem()
{
}

InGameMenuItemType InGameMenuItem::getType()
{
	return m_type;
}

bool InGameMenuItem::isSelecting()
{
	return m_isSelecting;
}

void InGameMenuItem::setIsSelecting(bool is)
{
	m_isSelecting = is;
	if (m_isSelecting) {
		setScale(1.5f);
	}
	else {
		setScale(1.f);
	}
}
