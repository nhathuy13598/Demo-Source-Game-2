#pragma once
#include "Framework.h"

class Star
{
public:
	Star();
	~Star();

	void setPosition(int x, int y);

	void setFlashing(float flashDelay);

	void setSpeed(float s);

	void update(float dt);
	void render();

	bool isEnd();
private:
	Point m_position;
	int m_size;
	float m_currentStarSpeed;
	float m_starAcceleration;
	float m_starSpeed;
	float m_posY;

	bool m_isFlashingOn;
	float m_flashingDelay;
	float m_currentFlashingDelay;
};