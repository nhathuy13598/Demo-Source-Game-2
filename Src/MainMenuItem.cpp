#include "MainMenuItem.h"
#include "SharedVariables.h"

#define NON_SELECT_SIZE 50

MainMenuItem::MainMenuItem(const char *text, MainMenuItemType t){
	m_sprite = new TextDisplay(text, SharedVariables::getInstance()->getFont(), NON_SELECT_SIZE);
	m_Type = t;
}

MainMenuItem::~MainMenuItem()
{
	delete m_sprite;
}

void MainMenuItem::setCenterX(int x) {
	m_sprite->centerX(x, 0);
}

void MainMenuItem::setCenterY(int y) {
	m_sprite->centerY(y, 0);
}

void MainMenuItem::setX(int x) {
	m_sprite->setX(x);
}

void MainMenuItem::setY(int y) {
	m_sprite->setY(y);
}

Rect MainMenuItem::getRect() {
	return m_sprite->getRect();
}

void MainMenuItem::update(float dt) {
	
}

void MainMenuItem::render() {
	m_sprite->render();
}

bool MainMenuItem::isSelected() {
	return m_isSelected;
}

void MainMenuItem::setSelecting(bool s) {
	m_isSelected = s;
	if (m_isSelected) {
		m_sprite->setScale(2);
	}
	else {
		m_sprite->setScale(1);
	}
}

MainMenuItemType MainMenuItem::getType() {
	return m_Type;
}