#include "Star.h"
#include "GameConfigInfo.h"
#include <algorithm>

Star::Star()
{
	m_position.x = rand() % DEF_WIDTH;
	m_position.y = rand() % (DEF_HEIGHT);
	m_posY = m_position.y;

	m_currentStarSpeed = 0.5;
	m_starAcceleration = 0;
	m_starSpeed = 0.1;

	m_isFlashingOn = true;
	m_currentFlashingDelay = (float)2 / (1 + rand() % 3);
	m_flashingDelay = m_currentFlashingDelay;

	m_size = 1 + rand() % 3;
}

Star::~Star()
{
}

void Star::setPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
	m_posY = y;
}

void Star::setFlashing(float flashDelay)
{
	m_isFlashingOn = true;
	m_currentFlashingDelay = flashDelay;
	m_flashingDelay = flashDelay;
}

void Star::setSpeed(float s)
{
	float delta = s - m_starSpeed;
	m_starAcceleration = delta / 300;
	m_starSpeed = s;
}

void Star::update(float dt)
{
	m_currentFlashingDelay -= dt;
	if (m_currentFlashingDelay <= 0) {
		m_currentFlashingDelay = m_flashingDelay;
		m_isFlashingOn = !m_isFlashingOn;
	}

	m_posY += m_currentStarSpeed;
	m_position.y = m_posY;
	if (m_currentStarSpeed != m_starSpeed) {
		m_currentStarSpeed += m_starAcceleration;
		if (m_starAcceleration < 0) {
			if (m_currentStarSpeed < m_starSpeed) {
				m_currentStarSpeed = m_starSpeed;
			}
		}
		else {
			if (m_currentStarSpeed > m_starSpeed) {
				m_currentStarSpeed = m_starSpeed;
			}
		}
	}
}

void Star::render()
{
	if (m_isFlashingOn)
		fwRenderRect(m_position.x, m_position.y, m_size, m_size);
}

bool Star::isEnd()
{
	return (m_position.y >= DEF_HEIGHT);
}
