#pragma once
#include "Star.h"
#include <vector>

class GameplayBackground
{
public:
	GameplayBackground();
	~GameplayBackground();

	void update(float dt);
	void render();

	void setSpeed(float min, float max);
private:
	float m_minSpeed;
	float m_maxSpeed;
	std::vector<Star*> *m_stars;
	int m_maxStarCount;
};
