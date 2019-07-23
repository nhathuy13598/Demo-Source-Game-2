#pragma once

#include "TextDisplay.h"

typedef enum InGameMenuItemType {
	InGameMenuItemType_CONTINUE,
	InGameMenuItemType_QUIT
} InGameMenuItemType;

class InGameMenuItem : public TextDisplay
{
public:
	InGameMenuItem(const char *text, InGameMenuItemType t);
	~InGameMenuItem();

	InGameMenuItemType getType();

	bool isSelecting();
	void setIsSelecting(bool is);
private:
	InGameMenuItemType m_type;
	bool m_isSelecting;
};